package org.kl.erase;

import org.kl.error.EraseException;
import org.kl.state.OverwrideMode;

public class EraseFS {
	static {
        System.loadLibrary("jefl"); 
    }
	
	public static native boolean eraseFile(String path) throws EraseException;
	
	public static native boolean eraseFile(String path, OverwrideMode mode) throws EraseException;
	
	public static native boolean eraseFiles(String... paths) throws EraseException;
	
	public static native boolean eraseFiles(OverwrideMode mode, String... paths) throws EraseException;
	
	public static native boolean eraseDirectory(String path, boolean recursived) throws EraseException;
	
	public static native boolean eraseDirectory(String path, OverwrideMode mode, boolean recursived) throws EraseException;
}
