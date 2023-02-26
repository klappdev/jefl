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

import org.junit.Test;
import java.io.File;

import static org.junit.Assert.*;
import static org.kl.jefl.FileUtils.ERASE_FILE1;
import static org.kl.jefl.FileUtils.ERASE_FILE2;
import static org.kl.jefl.FileUtils.FILES_DIRECTORY;

public final class FileEraserTest {

	@Test
	public void eraseFileSimpleModeTest() {
		System.out.println("\n> Start erasing file using simple mode\n");

		final var file = new File(FileUtils.createDirectory(FILES_DIRECTORY), ERASE_FILE1);
		final var filePath = file.getPath();
		FileUtils.fillFile(file, "Simple mode text");
		assertTrue(file.exists());

		System.out.println("Delete file " + filePath + "\n");
		try {
			System.out.println("Erase file " + filePath + "\n");

			final boolean fileDeleted = FileEraser.eraseFile(filePath, OverwriteMode.SIMPLE_MODE);

			assertTrue(fileDeleted);
		} catch (EraseException e) {
			System.err.println("Erase file " + filePath + " exception" + e.getMessage() + "\n");
		}

		assertFalse(file.exists());
	}

	@Test
	public void eraseFileOpenBsdModeTest() {
		System.out.println("\n> Start erasing file using openbsd mode\n");

		final var file = new File(FileUtils.createDirectory(FILES_DIRECTORY), ERASE_FILE2);
		final var filePath = file.getPath();
		FileUtils.fillFile(file, "Open bsd mode text");
		assertTrue(file.exists());

		System.out.println("Delete file " + filePath + "\n");
		try {
			System.out.println("Erase file " + filePath + "\n");

			final boolean fileDeleted = FileEraser.eraseFile(filePath, OverwriteMode.OPENBSD_MODE);

			assertTrue(fileDeleted);
		} catch (EraseException e) {
			System.err.println("Erase file " + filePath + " exception" + e.getMessage() + "\n");
		}

		assertFalse(file.exists());
	}

	@Test
	public void eraseFileDoeModeTest() {
		System.out.println("\n> Start erasing file using doe mode\n");

		final var file = new File(FileUtils.createDirectory(FILES_DIRECTORY), ERASE_FILE1);
		final var filePath = file.getPath();
		FileUtils.fillFile(file, "Doe mode text");
		assertTrue(file.exists());

		System.out.println("Delete file " + filePath + "\n");
		try {
			System.out.println("Erase file " + filePath + "\n");

			final boolean fileDeleted = FileEraser.eraseFile(filePath, OverwriteMode.DOE_MODE);

			assertTrue(fileDeleted);
		} catch (EraseException e) {
			System.err.println("Erase file " + filePath + " exception" + e.getMessage() + "\n");
		}

		assertFalse(file.exists());
	}

	@Test
	public void eraseFileRcmpModeTest() {
		System.out.println("\n> Start erasing file using rcmp mode\n");

		final var file = new File(FileUtils.createDirectory(FILES_DIRECTORY), ERASE_FILE2);
		final var filePath = file.getPath();
		FileUtils.fillFile(file, "Rcmp mode text");
		assertTrue(file.exists());

		System.out.println("Delete file " + filePath + "\n");
		try {
			System.out.println("Erase file " + filePath + "\n");

			final boolean fileDeleted = FileEraser.eraseFile(filePath, OverwriteMode.RCMP_MODE);

			assertTrue(fileDeleted);
		} catch (EraseException e) {
			System.err.println("Erase file " + filePath + " exception" + e.getMessage() + "\n");
		}

		assertFalse(file.exists());
	}

	@Test
	public void eraseFileDodModeTest() {
		System.out.println("\n> Start erasing file using dod mode\n");

		final var file = new File(FileUtils.createDirectory(FILES_DIRECTORY), ERASE_FILE1);
		final var filePath = file.getPath();
		FileUtils.fillFile(file, "Dod mode text");
		assertTrue(file.exists());

		System.out.println("Delete file " + filePath + "\n");
		try {
			System.out.println("Erase file " + filePath + "\n");

			final boolean fileDeleted = FileEraser.eraseFile(filePath, OverwriteMode.DOD_MODE);

			assertTrue(fileDeleted);
		} catch (EraseException e) {
			System.err.println("Erase file " + filePath + " exception" + e.getMessage() + "\n");
		}

		assertFalse(file.exists());
	}

	@Test
	public void eraseFileGutmanModeTest() {
		System.out.println("\n> Start erasing file using gutman mode\n");

		final var file = new File(FileUtils.createDirectory(FILES_DIRECTORY), ERASE_FILE2);
		final var filePath = file.getPath();
		FileUtils.fillFile(file, "Gutman mode text");
		assertTrue(file.exists());

		System.out.println("Delete file " + filePath + "\n");
		try {
			System.out.println("Erase file " + filePath + "\n");

			final boolean fileDeleted = FileEraser.eraseFile(filePath, OverwriteMode.GUTMAN_MODE);

			assertTrue(fileDeleted);
		} catch (EraseException e) {
			System.err.println("Erase file " + filePath + " exception" + e.getMessage() + "\n");
		}

		assertFalse(file.exists());
	}

	@Test
	public void eraseDirectorySimpleModeTest() {
		System.out.println("\n> Start native erasing directory with simple mode\n");

		final var directory = FileUtils.createDirectory(FILES_DIRECTORY);
		final String directoryPath = directory.getPath();

		final var file1 = new File(directory, ERASE_FILE1);
		FileUtils.fillFile(file1, "Simple mode text in file1");
		assertTrue(file1.exists());

		final var file2 = new File(directory, ERASE_FILE2);
		FileUtils.fillFile(file2, "Simple mode text in file2");
		assertTrue(file2.exists());

		try {
			System.out.println("Erase directory " + directoryPath + "\n");

			final boolean directoryDeleted = FileEraser.eraseDirectory(directoryPath, OverwriteMode.SIMPLE_MODE, false);

			assertTrue(directoryDeleted);
		} catch (EraseException e) {
			System.err.println("Erase directory " + directoryPath + " exception" + e.getMessage() + "\n");
		}
	}

	@Test
	public void eraseDirectoryOpenBsdModeTest() {
		System.out.println("\n> Start native erasing directory with openbsd mode\n");

		final var directory = FileUtils.createDirectory(FILES_DIRECTORY);
		final String directoryPath = directory.getPath();

		final var file1 = new File(directory, ERASE_FILE1);
		FileUtils.fillFile(file1, "Openbsd mode text in file1");
		assertTrue(file1.exists());

		final var file2 = new File(directory, ERASE_FILE2);
		FileUtils.fillFile(file2, "Openbsd mode text in file2");
		assertTrue(file2.exists());

		try {
			System.out.println("Erase directory " + directoryPath + "\n");

			final boolean directoryDeleted = FileEraser.eraseDirectory(directoryPath, OverwriteMode.OPENBSD_MODE, false);

			assertTrue(directoryDeleted);
		} catch (EraseException e) {
			System.err.println("Erase directory " + directoryPath + " exception" + e.getMessage() + "\n");
		}
	}

	@Test
	public void eraseDirectoryDoeModeTest() {
		System.out.println("\n> Start native erasing directory with doe mode\n");

		final var directory = FileUtils.createDirectory(FILES_DIRECTORY);
		final String directoryPath = directory.getPath();

		final var file1 = new File(directory, ERASE_FILE1);
		FileUtils.fillFile(file1, "Doe mode text in file1");
		assertTrue(file1.exists());

		final var file2 = new File(directory, ERASE_FILE2);
		FileUtils.fillFile(file2, "Doe mode text in file2");
		assertTrue(file2.exists());

		try {
			System.out.println("Erase directory " + directoryPath + "\n");

			final boolean directoryDeleted = FileEraser.eraseDirectory(directoryPath, OverwriteMode.DOE_MODE, false);

			assertTrue(directoryDeleted);
		} catch (EraseException e) {
			System.err.println("Erase directory " + directoryPath + " exception" + e.getMessage() + "\n");
		}
	}

	@Test
	public void eraseDirectoryRcmpModeTest() {
		System.out.println("\n> Start native erasing directory with rcmp mode\n");

		final var directory = FileUtils.createDirectory(FILES_DIRECTORY);
		final String directoryPath = directory.getPath();

		final var file1 = new File(directory, ERASE_FILE1);
		FileUtils.fillFile(file1, "Rcmp mode text in file1");
		assertTrue(file1.exists());

		final var file2 = new File(directory, ERASE_FILE2);
		FileUtils.fillFile(file2, "Rcmp mode text in file2");
		assertTrue(file2.exists());

		try {
			System.out.println("Erase directory " + directoryPath + "\n");

			final boolean directoryDeleted = FileEraser.eraseDirectory(directoryPath, OverwriteMode.RCMP_MODE, false);

			assertTrue(directoryDeleted);
		} catch (EraseException e) {
			System.err.println("Erase directory " + directoryPath + " exception" + e.getMessage() + "\n");
		}
	}

	@Test
	public void eraseDirectoryDodModeTest() {
		System.out.println("\n> Start native erasing directory with dod mode\n");

		final var directory = FileUtils.createDirectory(FILES_DIRECTORY);
		final String directoryPath = directory.getPath();

		final var file1 = new File(directory, ERASE_FILE1);
		FileUtils.fillFile(file1, "Dod mode text in file1");
		assertTrue(file1.exists());

		final var file2 = new File(directory, ERASE_FILE2);
		FileUtils.fillFile(file2, "Dod mode text in file2");
		assertTrue(file2.exists());

		try {
			System.out.println("Erase directory " + directoryPath + "\n");

			final boolean directoryDeleted = FileEraser.eraseDirectory(directoryPath, OverwriteMode.DOD_MODE, false);

			assertTrue(directoryDeleted);
		} catch (EraseException e) {
			System.err.println("Erase directory " + directoryPath + " exception" + e.getMessage() + "\n");
		}
	}

	@Test
	public void eraseDirectoryGutmanModeTest() {
		System.out.println("\n> Start native erasing directory with gutman mode\n");

		final var directory = FileUtils.createDirectory(FILES_DIRECTORY);
		final String directoryPath = directory.getPath();

		final var file1 = new File(directory, ERASE_FILE1);
		FileUtils.fillFile(file1, "Gutman mode text in file1");
		assertTrue(file1.exists());

		final var file2 = new File(directory, ERASE_FILE2);
		FileUtils.fillFile(file2, "Gutman mode text in file2");
		assertTrue(file2.exists());

		try {
			System.out.println("Erase directory " + directoryPath + "\n");

			final boolean directoryDeleted = FileEraser.eraseDirectory(directoryPath, OverwriteMode.GUTMAN_MODE, false);

			assertTrue(directoryDeleted);
		} catch (EraseException e) {
			System.err.println("Erase directory " + directoryPath + " exception" + e.getMessage() + "\n");
		}
	}


}
