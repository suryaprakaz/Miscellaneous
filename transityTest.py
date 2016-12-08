'''
 Write a program to encrypt a string that is passed. The encryption logic is as given below:
The string has to be written to a 6 column array. All spaces will be replaced by * (asterisk) as it is written. Any excess spaces left in the last row need to be filled with a . (dot). The encrypted string will be formed by reading the array vertically, one column after another.
 For eg: The beach in Chennai is the second longest in the world
'''


def encrypt(inp_str):
    # The encryption algorithm
    
    """Create a 2D list with six columns"""
    lists = [[] for i in range(6)]

    
    count = 0 #count helps discretize inputs
    for j in range(len(inp_str)/6+1):
        for i in range(6):
            #This 'excecption handling' hack helps suppress out of range errors
            try:
                if inp_str[i+6*count]==' ':
                    lists[i].append('*')
                else:
                    lists[i].append(inp_str[i+6*count])
            except:
                lists[i].append('.')
        count = count + 1

    #Print encrypted string
    encrypted_str = ""
    for i in lists:
        for j in i:
            encrypted_str = encrypted_str +j

    return encrypted_str

def decrypt(inp_str):
    
    #The decryption algorithm
    dec_list = [[] for i in range(6)]
    #Discretize input
    for i in range(6):
        dec_list[i] = inp_str[i*(len(inp_str)/6):i*(len(inp_str)/6)+(len(inp_str)/6)]
    
    dec_str = ""
    c = 0
    #Decryption loops
    for j in range(len(inp_str)/6):
        for i in range(6):
            if dec_list[i][c] == '*':
                dec_str = dec_str + ' '
            elif dec_list[i][c] != '*' and dec_list[i][c] != '.':
                dec_str = dec_str + dec_list[i][c]
            else:
                pass
        c = c + 1
    return dec_str

if __name__ == "__main__":
    inp_str = "The beach in Chennai is the second longest in the world"
    d_str = "Ta*atco*edhcCihoni*.ehh*engnw.**ei*de*o.binss*str.enn*elthl."
    print " The encrypted text is: "
    print encrypt(inp_str)
    print " The decrypted text is: "
    print decrypt(d_str)
    


