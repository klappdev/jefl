package org.kl;

import org.kl.erase.EraseFS;

public class Starter {

	public static void main(String[] args) {
		EraseFS.eraseDirectory("file/", false);
	}
}
