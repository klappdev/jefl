package org.kl;

import org.kl.erase.EraseFS;
import org.kl.error.EraseException;

public class Starter {

	public static void main(String[] args) throws EraseException {
		/*
			EraseFS.eraseFile("file/test_3.txt");
		*/
		
		EraseFS.eraseFiles("file/test_3.txt", "file/test_4.txt");
		
		/*
			EraseFS.eraseDirectory("file/", false);
		*/
	}
}
