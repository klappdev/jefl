package org.kl.erase;

import org.kl.state.OverrideMode;

public class EraseFS {
	static {
        System.loadLibrary("jefl"); 
    }
	
	public static native boolean eraseFile(String path);
	
	public static native boolean eraseFile(String path, OverrideMode mode);
	
	public static native boolean eraseFiles(String... paths);
	
	public static native boolean eraseFiles(OverrideMode mode, String... paths);
	
	public static native boolean eraseDirectory(String path, boolean recursived);
	
	public static native boolean eraseDirectory(String path, OverrideMode mode, boolean recursived);
}
