import re
import sys

def find_function_body(code: str, function_name: str) -> tuple[int, int] | None:
    """
    Finds the start and end indices of a function's body in C code.
    Handles nested braces.
    """
    # Regex to find the function signature and the first opening brace
    # Example: "void sbox(...) {"
    # We use \b for word boundaries to ensure we don't match a function name that is a substring of another.
    match = re.search(
        rf"\b{function_name}\b\s*\([^)]*\)\s*{{", code, re.DOTALL
    )
    if not match:
        return None

    body_start_index = match.end()
    brace_level = 1
    
    for i in range(body_start_index, len(code)):
        if code[i] == '{':
            brace_level += 1
        elif code[i] == '}':
            brace_level -= 1
        
        if brace_level == 0:
            # We found the matching closing brace for the function
            body_end_index = i
            return body_start_index, body_end_index
            
    return None # Matching brace not found

def refactor_function(code: str, function_name: str) -> str:
    """
    Refactors the specified function to remove redundant input variable assignments.
    """
    # 1. Isolate the function body
    indices = find_function_body(code, function_name)
    if not indices:
        print(f"Error: Function '{function_name}' not found or has malformed braces.")
        return code

    body_start, body_end = indices
    
    # Split the code into three parts
    code_before = code[:body_start]
    function_body = code[body_start:body_end]
    code_after = code[body_end:]

    # 2. Find all redundant assignments and build a replacement map
    # Pattern: x0_inp = x0; (allows for different suffixes, not just _inp)
    assignment_pattern = re.compile(r"^\s*(\w+_inp)\s*=\s*(\w+);", re.MULTILINE)
    
    # Create a map like {'x0_inp': 'x0', 'dec_1_inp': 'dec_1'}
    replacement_map = {
        match.group(1): match.group(2)
        for match in assignment_pattern.finditer(function_body)
    }

    if not replacement_map:
        print(f"No redundant assignments using the '*_inp' pattern found in function '{function_name}'. The code is already clean.")
        return code

    print(f"Found the following variables to replace in function '{function_name}':")
    for inp_var, original_var in replacement_map.items():
        print(f"  - Replacing '{inp_var}' with '{original_var}'")

    # 3. Perform the cleaning operations on the function body
    
    # 3a. Remove the declaration lines (e.g., "_Bool x0_inp;")
    vars_to_remove = "|".join(replacement_map.keys())
    declaration_pattern = re.compile(
        rf"^\s*(_Bool|int)\s+({vars_to_remove})\s*;\s*$", re.MULTILINE
    )
    cleaned_body = declaration_pattern.sub("", function_body)
    
    # 3b. Remove the assignment lines
    cleaned_body = assignment_pattern.sub("", cleaned_body)

    # 3c. Replace all occurrences of the _inp variables with the original ones
    for inp_var, original_var in replacement_map.items():
        # Use \b for word boundaries to avoid partial replacements
        cleaned_body = re.sub(r'\b' + inp_var + r'\b', original_var, cleaned_body)

    # 4. Reassemble the full code
    refactored_code = code_before + cleaned_body + code_after
    
    return refactored_code


def main():
    """Main function to run the script."""
    if len(sys.argv) != 4:
        print("Usage: python refactor_script.py <function_name> <input_c_file> <output_c_file>")
        sys.exit(1)

    function_name_to_refactor = sys.argv[1]
    input_path = sys.argv[2]
    output_path = sys.argv[3]

    try:
        with open(input_path, 'r') as f:
            original_code = f.read()
    except FileNotFoundError:
        print(f"Error: Input file '{input_path}' not found.")
        sys.exit(1)

    # Process the code
    new_code = refactor_function(original_code, function_name_to_refactor)

    # Write the result to the output file
    with open(output_path, 'w') as f:
        f.write(new_code)
        
    print(f"\n✅ Refactoring complete! Cleaned code saved to '{output_path}'.")


if __name__ == "__main__":
    main()
