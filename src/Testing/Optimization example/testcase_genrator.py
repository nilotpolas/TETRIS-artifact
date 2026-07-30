import csv

def c_logic_model(a, b, c, d):
    """
    Simulates the logic of the provided C function in Python.
    """
    # y = a & b;
    y = a & b
    
    # z = y & b;
    z = y & b
    
    # x = y & c;
    x = y & c
    
    # t = y & d;
    t = y & d
    
    # p = z & x;
    p = z & x
    
    # q = t & d;
    q = t & d
    
    # e = p & q;
    e = p & q
    
    # * r = e ^ q;
    r = e ^ q
    
    return r

def main():
    filename = "expected_outputs.csv"
    
    # Define the header for the CSV file
    header = ['a', 'b', 'c', 'd', 'r_expected']
    
    data = []
    
    print(f"Generating inputs and outputs for {filename}...\n")
    print(f"{'a':<3} {'b':<3} {'c':<3} {'d':<3} | {'r':<3}")
    print("-" * 20)

    # Iterate through all 16 possibilities (0 to 15)
    # Binary representation of i will serve as inputs a, b, c, d
    for i in range(16):
        # Extract bits. 
        # Example: if i is 13 (binary 1101), a=1, b=1, c=0, d=1
        a = (i >> 3) & 1  # MSB
        b = (i >> 2) & 1
        c = (i >> 1) & 1
        d = (i >> 0) & 1  # LSB
        
        # Get the expected output from the logic model
        r = c_logic_model(a, b, c, d)
        
        # Print to console for verification
        print(f"{a:<3} {b:<3} {c:<3} {d:<3} | {r:<3}")
        
        # Add to data list
        data.append([a, b, c, d, r])

    # Write data to CSV
    with open(filename, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(header)
        writer.writerows(data)
        
    print(f"\nSuccessfully wrote 16 test vectors to {filename}")

if __name__ == "__main__":
    main()