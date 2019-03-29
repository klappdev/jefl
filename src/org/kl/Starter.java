package org.kl;

import org.kl.erase.EraseFS;
import org.kl.error.EraseException;
import org.kl.state.OverwrideMode;

public class Starter {

	public static void main(String[] args) throws EraseException {
		/**/
			EraseFS.eraseFile("file/test_1.txt");
			EraseFS.eraseFile("file/test_1.txt", OverwrideMode.SIMPLE_MODE);
			EraseFS.eraseFile("file/test_1.txt", OverwrideMode.OPENBSD_MODE);
			EraseFS.eraseFile("file/test_1.txt", OverwrideMode.DOE_MODE);
			EraseFS.eraseFile("file/test_1.txt", OverwrideMode.RCMP_MODE);
			
			EraseFS.eraseFiles("file/test_1.txt", "file/test_2.txt");
			EraseFS.eraseFiles(OverwrideMode.SIMPLE_MODE,  "file/test_1.txt", "file/test_2.txt");
			EraseFS.eraseFiles(OverwrideMode.OPENBSD_MODE, "file/test_1.txt", "file/test_2.txt");
			EraseFS.eraseFiles(OverwrideMode.DOE_MODE, "file/test_1.txt", "file/test_2.txt");
			EraseFS.eraseFiles(OverwrideMode.RCMP_MODE, "file/test_1.txt", "file/test_2.txt");

			EraseFS.eraseDirectory("file/", false);
			EraseFS.eraseDirectory("file/", OverwrideMode.SIMPLE_MODE, false);
			EraseFS.eraseDirectory("file/", OverwrideMode.OPENBSD_MODE, false);
			EraseFS.eraseDirectory("file/", OverwrideMode.DOE_MODE, false);
			EraseFS.eraseDirectory("file/", OverwrideMode.RCMP_MODE, false);
		/**/
	}
}
