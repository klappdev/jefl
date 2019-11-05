package org.kl.test;

import org.kl.erase.EraseFS;
import org.kl.error.EraseException;
import org.kl.state.OverwrideMode;

public class EraseTest {

	public static void eraseFileTest() throws EraseException {
		EraseFS.eraseFile("file/test_1.txt");
		EraseFS.eraseFile("file/test_1.txt", OverwrideMode.SIMPLE_MODE);
		EraseFS.eraseFile("file/test_1.txt", OverwrideMode.OPENBSD_MODE);
		EraseFS.eraseFile("file/test_1.txt", OverwrideMode.DOE_MODE);
		EraseFS.eraseFile("file/test_1.txt", OverwrideMode.RCMP_MODE);
		EraseFS.eraseFile("file/test_1.txt", OverwrideMode.DOD_MODE);
		EraseFS.eraseFile("file/test_1.txt", OverwrideMode.GUTMAN_MODE);
	}
	
	public static void eraseFilesTest() throws EraseException {
		EraseFS.eraseFiles("file/test_1.txt", "file/test_2.txt");
		EraseFS.eraseFiles(OverwrideMode.SIMPLE_MODE, "file/test_1.txt", "file/test_2.txt");
		EraseFS.eraseFiles(OverwrideMode.OPENBSD_MODE, "file/test_1.txt", "file/test_2.txt");
		EraseFS.eraseFiles(OverwrideMode.DOE_MODE, "file/test_1.txt", "file/test_2.txt");
		EraseFS.eraseFiles(OverwrideMode.RCMP_MODE, "file/test_1.txt", "file/test_2.txt");
		EraseFS.eraseFiles(OverwrideMode.DOD_MODE, "file/test_1.txt", "file/test_2.txt");
		EraseFS.eraseFiles(OverwrideMode.GUTMAN_MODE, "file/test_1.txt", "file/test_2.txt");
	}
	
	public static void eraseDirectoryTest() throws EraseException {
		EraseFS.eraseDirectory("file/", false);
		EraseFS.eraseDirectory("file/", OverwrideMode.SIMPLE_MODE, false);
		EraseFS.eraseDirectory("file/", OverwrideMode.OPENBSD_MODE, false);
		EraseFS.eraseDirectory("file/", OverwrideMode.DOE_MODE, false);
		EraseFS.eraseDirectory("file/", OverwrideMode.RCMP_MODE, false);
		EraseFS.eraseDirectory("file/", OverwrideMode.DOD_MODE, true);
		EraseFS.eraseDirectory("file/", OverwrideMode.GUTMAN_MODE, true);
	}
	
	public static void main(String[] args) throws EraseException {
		eraseFileTest();
		eraseFilesTest();
		eraseDirectoryTest();
	}
}
