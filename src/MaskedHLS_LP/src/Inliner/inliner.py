import sys
import json
from DiGraph import DiGraph
from Visitors import FunctionVisitor,DeclVisitor,ArrayValueReplacer,AssignmentChecker,ConstToVar
from utils import extractFunctionInfo,processDependantFunctions,generate_c_file,insertAssignmentsAndDeclForConstants

sys.path.extend(['.', '..'])

from pycparser import parse_file, c_ast

def _is_param_assigned(funcdef: c_ast.FuncDef, param_name: str) -> bool:
    class AssignFinder(c_ast.NodeVisitor):
        def __init__(self):
            self.found = False
        def visit_Assignment(self, node):
            if isinstance(node.lvalue, c_ast.ID) and node.lvalue.name == param_name:
                self.found = True
            self.generic_visit(node)
    finder = AssignFinder()
    if funcdef.body:
        finder.visit(funcdef.body)
    return finder.found

def _replace_id(node, old_name: str, new_name: str):
    if node is None:
        return
    if isinstance(node, c_ast.ID):
        if node.name == old_name:
            node.name = new_name
        return
    for _, child in node.children():
        _replace_id(child, old_name, new_name)

def clean_redundant_shadows(ast):
    """
    Improved cleaning pass:
    - Finds Decl(name_inp) even if many declarations are grouped at top.
    - Locates the later assignment 'name_inp = src;' (may be separated by other Decls).
    - Builds shadow->source pairs and collapses chains that terminate at a function parameter
      (only when that parameter is never assigned in the function).
    - Removes the corresponding Decl + Assignment nodes and replaces uses.
    """
    for ext in ast.ext:
        if not isinstance(ext, c_ast.FuncDef):
            continue
        func = ext
        # collect parameter names
        params = []
        if isinstance(func.decl.type, c_ast.FuncDecl) and func.decl.type.args:
            for p in func.decl.type.args.params:
                if isinstance(p, c_ast.Decl) and p.name:
                    params.append(p.name)
        block_items = func.body.block_items
        if not block_items or len(block_items) < 2:
            continue

        changed = True
        while changed:
            changed = False
            # collect all shadow declarations (name -> decl_idx)
            decl_positions = {}
            for i, node in enumerate(block_items):
                if isinstance(node, c_ast.Decl) and isinstance(node.type, c_ast.TypeDecl):
                    name = node.name
                    if name and name.endswith('_inp'):
                        decl_positions[name] = i

            # locate matching assignment for each decl (search forward)
            pairs = {}       # shadow -> source name
            positions = {}   # shadow -> (decl_idx, assign_idx)
            for shadow, didx in decl_positions.items():
                for j in range(didx + 1, len(block_items)):
                    anode = block_items[j]
                    if isinstance(anode, c_ast.Assignment):
                        l = anode.lvalue
                        r = anode.rvalue
                        if isinstance(l, c_ast.ID) and l.name == shadow and isinstance(r, c_ast.ID):
                            pairs[shadow] = r.name
                            positions[shadow] = (didx, j)
                            break
                    # continue searching (allow intervening decls)

            if not pairs:
                break

            # try collapsing any chain that ends at a parameter and is safe
            for shadow in list(pairs.keys()):
                # follow chain: shadow -> src -> ...
                chain = []
                cur = shadow
                visited = set()
                while cur in pairs and cur not in visited:
                    visited.add(cur)
                    chain.append(cur)
                    cur = pairs[cur]
                base = cur
                # If base is parameter and not assigned, we can collapse entire chain
                if base in params and not _is_param_assigned(func, base):
                    # gather all decl/assign indices to remove
                    remove_indices = []
                    involved_names = set(chain)
                    # include any intermediate shadows in pairs mapping that appear in chain traversal
                    for name in list(involved_names):
                        if name in positions:
                            d_idx, a_idx = positions[name]
                            remove_indices.extend([d_idx, a_idx])
                    # also include any other declared shadows that point directly to base (rare)
                    for name, (d_idx, a_idx) in positions.items():
                        if pairs.get(name) == base:
                            involved_names.add(name)
                            remove_indices.extend([d_idx, a_idx])

                    if not remove_indices:
                        continue

                    # perform replacement of all involved shadow names to base in subsequent block items
                    min_decl_idx = min(remove_indices)
                    for k in range(min_decl_idx + 2, len(block_items)):
                        for nm in involved_names:
                            _replace_id(block_items[k], nm, base)

                    # delete nodes from highest index to lowest
                    for idx in sorted(set(remove_indices), reverse=True):
                        try:
                            del block_items[idx]
                        except Exception:
                            pass

                    changed = True
                    break
            # end for
        # end while

def mainInline(inputFile,outputFile,topModule,turn=2):
    """
    @brief Processes a C source file to inline functions, handle constants, and generate a new C file.

    This function parses the provided C source file, constructs a directed graph of functions, performs topological
    sorting, processes functions based on dependencies, handles array and constant values, and finally generates
    an updated C source file.

    @param inputFile: The path to the input C source file to be processed.
    @type inputFile: str
    @param outputFile: The path where the processed C source file will be saved.
    @type outputFile: str
    @param topModule: The name of the top-level module (function) to be used as the entry point.
    @type topModule: str

    @raises SystemExit: If the top module is not found in the sorted function list or if no functions are present.
    """
    ast = parse_file(inputFile, use_cpp=True)
    arrMap = {}
    arrVisitor = DeclVisitor(arrayMap=arrMap,ast=ast)
    arrVisitor.visit(ast)
    functionGraph = DiGraph()
    functionInfo = {}

    for fDef in ast.ext:
        if isinstance(fDef,c_ast.FuncDef):
            functionGraph.addFunction(fDef.decl.name)
            visitor = FunctionVisitor(functionGraph,fDef.decl.name)
            visitor.visit(fDef)

    sortedList = functionGraph.topoSort()
    if topModule not in sortedList:
        print(f"No top module named {topModule} in given input file.")
        print("Note : The name of module is case sensitive")
        sys.exit(1)
    if(len(sortedList) == 1):
        # clean shadows before generating output
        clean_redundant_shadows(ast)
        generate_c_file(ast,outputFile)

    # print(f"sortedList : {sortedList}")
    for function in sortedList:
        inDegree = functionGraph.getIndegreeOf(function)
        if inDegree == 0 and function != topModule:
            for fDef in ast.ext[:]:
                if isinstance(fDef,c_ast.FuncDef) and fDef.decl.name == function:
                    extractFunctionInfo(fDef,functionInfo)
                    ast.ext.remove(fDef)
                    break
        
        elif function != topModule:
            for fDef in ast.ext[:]:
                if isinstance(fDef,c_ast.FuncDef) and fDef.decl.name == function:
                    processDependantFunctions(fDef,functionInfo,False)
                    extractFunctionInfo(fDef,functionInfo)
                    ast.ext.remove(fDef)
                    break
        else:
            for fDef in ast.ext[:]:
                # print(f"fDef : {fDef.decl.name}")
                if isinstance(fDef,c_ast.FuncDef) and fDef.decl.name == function:
                    processDependantFunctions(fDef,functionInfo,True)
    
    for fDef in ast.ext[:]:
        if isinstance(fDef,c_ast.Decl) and isinstance(fDef.type,c_ast.ArrayDecl):
            ast.ext.remove(fDef)

    constArr = []
    arrValueReplacer = ArrayValueReplacer(arrMap,constArr)
    arrValueReplacer.visit(ast)
    if turn == 1:
        constToVar = ConstToVar()
        constToVar.visit(ast)
        insertAssignmentsAndDeclForConstants(ast,constArr)

    assignmentChecker = AssignmentChecker();
    assignmentChecker.visit(ast)
    # run cleaning pass to remove redundant <name>_inp helpers
    clean_redundant_shadows(ast)
    generate_c_file(ast,outputFile)



if __name__ == "__main__":
    # with open(r'.\MaskedHLS_LP\src\systemArgs.json', 'r') as file:
    print()
    with open('./systemArgs.json', 'r') as file:
        args = json.load(file)
    mainInline(args['inputFile'],args["inlinerOutput"],args['topModule'], args['turn'])