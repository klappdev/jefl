# jefl

This is simple Java library for secure erase files.

When we remove file, remove only name file but content file stay exist. <br/>
Sometimes we want that file content can not be recovery again.

For secure erase file used next steps:

    > overwrite content file
    > truncate file 
    > random rename file
    > delete file
  
There are the following methods of overwrite content file:

    > Simple  method - overwrite 1 pass 0x00 bytes   
    > DOE     method - overwrite 3 pass random, random, "DoE"     
    > RCMP    method - overwrite 3 pass 0x00 ,0xFF, "RCMP"
    > OPENBSD method - overwrite 3 pass 0xFF, 0x00, 0xFF bytes
    > DOD     method - overwrite 7 pass 
    > Gutmann method - overwrite 35 pass  

Using this library developer can erase files in the following way.

```Java
  native boolean eraseFile(String path) throws EraseException;
	
  native boolean eraseFile(String path, OverwrideMode mode) throws EraseException;
	
  native boolean eraseFiles(String... paths) throws EraseException;
	
  native boolean eraseFiles(OverwrideMode mode, String... paths) throws EraseException;
	
  native boolean eraseDirectory(String path, boolean recur) throws EraseException;
	
  native boolean eraseDirectory(String path, OverwrideMode mode, boolean recur) throws EraseException;
```
Verified:<br/>
Static analizer clang     <br/>
Dynamic analizer valgrind <br/>

Requirements:<br/>
Java version: 8  <br/>
C++  version: 17 <br/>

