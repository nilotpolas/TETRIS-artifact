import re
from collections import defaultdict

def remove_redundant_registers(input_file, output_file):
    """
    Remove only UNBALANCED register chains (3+ of same share).
    Keep BALANCED pairs (share_0 and share_1 registered together).
    
    Improved algorithm:
    1. Parse all register assignments: var = reg(input)
    2. Build dependency graph: var -> input
    3. Detect chains of length 3+: a->b->c->d all same share
    4. Keep only first in chain, remove intermediate ones
    5. Preserve balanced pairs (share_0 and share_1 together)
    """
    
    with open(input_file, 'r') as f:
        content = f.read()
    
    lines = content.split('\n')
    
    # Step 1: Parse all register operations
    # Pattern: var = reg(input);
    reg_pattern = r'(\w+)\s*=\s*reg\((\w+)\);'
    
    registers = {}  # var -> input_var
    reg_locations = {}  # var -> (line_number, full_line)
    
    for line_num, line in enumerate(lines):
        match = re.search(reg_pattern, line)
        if match:
            output_var = match.group(1)
            input_var = match.group(2)
            registers[output_var] = input_var
            reg_locations[output_var] = (line_num, line)
    
    print(f"[ANALYSIS] Found {len(registers)} register operations")
    
    # Step 2: Build dependency chains
    # For each var, trace back how deep the chain is
    def get_chain_depth(var, visited=None):
        """Get the depth of the register chain for this variable."""
        if visited is None:
            visited = set()
        
        if var in visited or var not in registers:
            return 1
        
        visited.add(var)
        input_var = registers[var]
        return 1 + get_chain_depth(input_var, visited.copy())
    
    # Step 3: Find variables with same base name but different shares
    def extract_base_name(var):
        """Extract base name from z_0, z_1 -> 'z'"""
        match = re.match(r'(\w+?)(_0|_1)?$', var)
        if match:
            return match.group(1)
        return var
    
    # Step 4: Identify chains to remove
    vars_to_remove = set()
    chains_found = defaultdict(list)
    
    for output_var in registers:
        base_name = extract_base_name(output_var)
        share_suffix = output_var[len(base_name):] if output_var.startswith(base_name) else ''
        
        # Build the chain for this variable
        chain = []
        current = output_var
        visited = set()
        
        while current in registers and current not in visited:
            visited.add(current)
            chain.append(current)
            current = registers[current]
        
        chain_length = len(chain)
        chain_key = (base_name, share_suffix)
        chains_found[chain_key].append((output_var, chain_length, chain))
        
        # If chain is 3+ long AND same share suffix throughout:
        if chain_length >= 3:
            # Check if all vars in chain have same share suffix
            all_same_share = all(
                extract_base_name(v)[len(extract_base_name(v)):] == share_suffix
                or re.search(f'{share_suffix}$', v)
                for v in chain
            )
            
            # Check if there's a balanced counterpart
            opposite_suffix = '_1' if share_suffix == '_0' else '_0'
            has_counterpart = any(
                extract_base_name(v) == base_name and 
                (re.search(f'{opposite_suffix}$', v) or opposite_suffix in v)
                for v in registers
            )
            
            if all_same_share and not has_counterpart:
                # Mark intermediate registers for removal (keep first, remove rest)
                for var_to_check in chain[1:]:
                    vars_to_remove.add(var_to_check)
                
                print(f"[CHAIN FOUND] {chain_key}: {' -> '.join(chain)} (length={chain_length})")
                print(f"              Marked for removal: {', '.join(chain[1:])}")
    
    # Step 5: Also detect unbalanced isolated chains
    # (Variables registered but no matching opposite share variant)
    for output_var, input_var in registers.items():
        base_name = extract_base_name(output_var)
        
        # Extract share suffix more carefully
        if output_var.endswith('_0'):
            share_suffix = '_0'
        elif output_var.endswith('_1'):
            share_suffix = '_1'
        else:
            continue
        
        opposite_suffix = '_1' if share_suffix == '_0' else '_0'
        expected_counterpart = base_name + opposite_suffix
        
        # Check if counterpart exists in the register operations
        has_counterpart = expected_counterpart in registers
        
        if not has_counterpart:
            # This is unbalanced - check if it's part of a chain
            depth = get_chain_depth(output_var)
            if depth >= 2:
                # It's part of a chain - consider it for removal
                # But only remove if it's not the first in the chain
                if input_var in registers:
                    # This variable is an intermediate or end of chain
                    # Mark it for potential removal
                    pass
    
    # Step 6: Remove marked variables from code
    print(f"\n[REMOVAL] Removing {len(vars_to_remove)} register operations:")
    
    removed_count = 0
    result_lines = []
    
    for line_num, line in enumerate(lines):
        # Check if this line declares or assigns any marked variable
        should_remove = False
        
        for var in vars_to_remove:
            # Pattern 1: _Bool var; (declaration)
            if re.search(rf'\b_Bool\s+{re.escape(var)}\b', line):
                should_remove = True
                removed_count += 1
                print(f"  [-] Line {line_num + 1}: {line.strip()[:70]}")
                break
            
            # Pattern 2: var = reg(...); (assignment)
            if re.search(rf'\b{re.escape(var)}\s*=\s*reg\(', line):
                should_remove = True
                removed_count += 1
                print(f"  [-] Line {line_num + 1}: {line.strip()[:70]}")
                break
        
        if not should_remove:
            result_lines.append(line)
    
    # Write optimized content
    with open(output_file, 'w') as f:
        f.write('\n'.join(result_lines))
    
    print(f"\n[SUCCESS] Removed unbalanced register chains")
    print(f"[STATS] Removed {removed_count} redundant lines")
    print(f"[CHAINS] Total chains detected: {len(chains_found)}")
    print(f"Output: {output_file}")

if __name__ == "__main__":
    input_file = "/home/tapish08/Desktop/DSE-Framework/MaskedHLS_LP/src/tempFiles/postProcessedOut.c"
    output_file = "/home/tapish08/Desktop/DSE-Framework/MaskedHLS_LP/src/tempFiles/postProcessedOut.c"
    
    remove_redundant_registers(input_file, output_file)
