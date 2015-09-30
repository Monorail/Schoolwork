cd src
javac crcfile.java
jar -cvmf MANIFEST.MF crcfile.jar crcfile.class 
cp crcfile.jar ../crcfile.jar
rm crcfile.jar
rm crcfile.class
