#!/usr/bin/python

import random, sys
from optparse import OptionParser

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE1 FILE2

Output comparison between FILE1 and FILE2."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-1",
                      action="store_true", dest="opt1", default=False,
                      help="Excludes the 1st Column")
    parser.add_option("-2",
                      action="store_true", dest="opt2", default=False,
                      help="Excludes the 2nd Column")
    parser.add_option("-3",
                      action="store_true", dest="opt3", default=False,
                      help="Excludes the 3rd Column")
    parser.add_option("-u",
                      action="store_true", dest="optU", default=False,
                      help="Unsorted Output")
    options, args = parser.parse_args(sys.argv[1:])

    if len(args) != 2:
        parser.error("Wrong number of operands")
    
    input_arg1 = args[0]
    input_arg2 = args[1]

    list1 = []
    list2 = []
#Moving the files into two different lists    
    try:
        if (input_arg1 == "-"): #STDIN
            list1 = sys.stdin.readlines()
        else:
            f1 = open(input_arg1, 'r')
            list1 = f1.readlines()
            f1.close()
    except:
        parser.error("I/O Error: Invalid Input")
    
    try:
        if (input_arg2 == "-"): #STDIN
            list2 = sys.stdin.readlines()
        else:
            f2 = open (input_arg2, 'r')
            list2 = f2.readlines()
            f2.close()
    except:
        parser.error("I/O Error: Invalid Input")
        
#Comparing the Strings
    comm_out = [] #List of the words
    comm_pos = [] #List of which column the words are in
    
    #Sorted Output
    try:
        if (options.optU==False):
            i = 0
            j = 0
            while (i < len(list1) and j < len(list2)):
                if (list1[i] == list2[j]): #They are the same - goes in col3
                    comm_out.append(list1[i])
                    comm_pos.append(3)
                    i+=1
                    j+=1
                    continue
                elif (list2[j] > list1[i]): #Only in Column 1 and occurs 1st
                    comm_out.append(list1[i])
                    comm_pos.append(1)
                    i+=1
                    continue
                else: #Only in Column 2 and occurs 1st
                    comm_out.append(list2[j])
                    comm_pos.append(2)
                    j+=1
                    continue

            if (i != len(list1)): #If list2 is shorter, puts remainder of list1
                while (i < len(list1)): #into column 1
                    comm_out.append(list1[i])
                    comm_pos.append(1)
                    i+=1
                    
            if (j != len(list2)): #If list1 is shorter, puts remainder of list2
                while (j < len(list2)): #into column 2
                    comm_out.append(list2[j])
                    comm_pos.append(2)
                    j+=1
    except:
        parser.error("Error comparing files")
    
    #Unsorted Output
    try:
        if (options.optU==True):
            for word1 in list1: #Puts the common word into column 3
                notSame = True #Variable to Check if there is a common word
                for word2 in list2:
                    if (word1 == word2): #Word appears in both lists
                        comm_out.append(word1)
                        comm_pos.append(3)
                        list2.remove(word2)
                        notSame = False
                        break
                if (notSame == True): #Puts all the words only in list1
                    comm_out.append(word1) #into the first column
                    comm_pos.append(1)
            for word2 in list2: #Puts all the words only in list2
                comm_out.append(word2) #into the second column
                comm_pos.append(2)
    except:
        parser.error("Error comparing files")

    for i in range(len (comm_out)):
        if (options.opt1 == True):
            if (options.opt2 == True):
                if (options.opt3 == True): #Option -123
                    break
                if (comm_pos[i] == 3): #Option -12
                    sys.stdout.write(comm_out[i])
            elif (options.opt2 == False): #Option -1
                if (comm_pos[i] == 2):
                    sys.stdout.write(comm_out[i])
                elif (comm_pos[i] == 3):
                    sys.stdout.write("\t"+comm_out[i])
        if (options.opt1 == False):
            if (options.opt2 == True):
                if (options.opt3 == True): #Option -23
                    if (comm_pos[i] == 1):
                        sys.stdout.write(comm_out[i])
                elif (options.opt3 == False): #Option -2
                    if (comm_pos[i] == 1):
                        sys.stdout.write(comm_out[i])
                    elif (comm_pos[i] == 3):
                        sys.stdout.write("\t"+comm_out[i])
            elif (options.opt2 == False):
                if (options.opt3 == True): #Option -3
                    if (comm_pos[i] == 1):
                        sys.stdout.write(comm_out[i])
                    elif (comm_pos[i] == 2):
                        sys.stdout.write("\t"+comm_out[i])
                elif (options.opt3 == False): #Output all
                    if (comm_pos[i] == 1):
                        sys.stdout.write(comm_out[i])
                    elif (comm_pos[i] == 2):
                        sys.stdout.write("\t"+comm_out[i])
                    elif (comm_pos[i] == 3):
                        sys.stdout.write("\t\t"+comm_out[i])

if __name__ == "__main__":
    main()
