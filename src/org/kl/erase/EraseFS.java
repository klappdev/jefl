package org.kl.erase;

import org.kl.state.OverwrideMode;

public class EraseFS {
	static {
        System.loadLibrary("jefl"); 
    }
	
	public static native boolean eraseFile(String path);
	
	public static native boolean eraseFile(String path, OverwrideMode mode);
	
	public static native boolean eraseFiles(String... paths);
	
	public static native boolean eraseFiles(OverwrideMode mode, String... paths);
	
	public static native boolean eraseDirectory(String path, boolean recursived);
	
	public static native boolean eraseDirectory(String path, OverwrideMode mode, boolean recursived);
}
