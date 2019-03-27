package org.kl;

import org.kl.erase.EraseFS;
import org.kl.error.EraseException;

public class Starter {

	public static void main(String[] args) throws EraseException {
		EraseFS.eraseDirectory("file/", false);
	}
}
