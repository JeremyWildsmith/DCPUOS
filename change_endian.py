with open('.\\DARKCPU\\DARKCPU.bin', 'rb') as inputFile:
    with open('image.bin', 'wb') as outputFile:
        while True:
            bufA = inputFile.read(1)
            bufB = inputFile.read(1)
            if bufA == "" or bufB == "":
                break;
            
            outputFile.write(bufB)
            outputFile.write(bufA)
            
