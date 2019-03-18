package org.kl;

import org.kl.erase.EraseFS;
import org.kl.state.OverrideMode;

public class Starter {

	public static void main(String[] args) {
		EraseFS.eraseFile("file/test_1.txt", OverrideMode.RCMP_MODE);
	}
}
