/*
 * Licensed under the MIT License <http://opensource.org/licenses/MIT>.
 * SPDX-License-Identifier: MIT
 * 
 * Copyright (c) 2019-2023 https://github.com/klappdev
 *
 * Permission is hereby  granted, free of charge, to any  person obtaining a copy
 * of this software and associated  documentation files (the "Software"), to deal
 * in the Software  without restriction, including without  limitation the rights
 * to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
 * copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
 * IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
 * FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
 * AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
 * LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
package org.kl.jefl;

import java.io.File;
import java.io.FileWriter;

public final class FileUtils {
	public final static String ERASE_FILE1 = "erase1.txt";
	public final static String ERASE_FILE2 = "erase2.txt";
	public static final String FILES_DIRECTORY = "files";
	private static final int COUNT_LINES = 50;
	
	/*package-private*/ static File createDirectory(String folder) {
		final var directory = new File(folder);

		if (!directory.exists()) {
			if (!directory.mkdir()) {
				System.out.println("Directory " + folder + " didn't created\n");
			}
		}

		return directory;
	}

	/*package-private*/ static void fillFile(File file, String text) {
		try {
			final var writer = new FileWriter(file);

			for (int i = 0; i < COUNT_LINES; i++) {
				writer.append(text)
				.append(" ")
				.append(String.valueOf(i))
				.append("\n");
			}

			writer.flush();
			writer.close();
		} catch (Exception e) {
			System.err.println("File write exception: " + e.getMessage() + "\n");
		}
	}
}
