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
import java.util.concurrent.TimeUnit;

import org.openjdk.jmh.annotations.*;
import org.openjdk.jmh.runner.Runner;
import org.openjdk.jmh.runner.options.Options;
import org.openjdk.jmh.runner.options.OptionsBuilder;

import static org.kl.jefl.FileUtils.ERASE_FILE1;
import static org.kl.jefl.FileUtils.ERASE_FILE2;
import static org.kl.jefl.FileUtils.FILES_DIRECTORY;

@Warmup(iterations = 3, time = 1)
@Measurement(iterations = 3, time = 1)
@Fork(3)
@State(Scope.Thread)
@BenchmarkMode(Mode.AverageTime)
@OutputTimeUnit(TimeUnit.NANOSECONDS)
public class FileEraserBenchmark {
    private String eraseFilePath1;
    private String eraseFilePath2;

    @Setup
    public void setup() {
    	final var eraseFile1 = new File(FileUtils.createDirectory(FILES_DIRECTORY), ERASE_FILE1);
		FileUtils.fillFile(eraseFile1, "Erase file 1");
		eraseFilePath1 = eraseFile1.getPath();
		
		final var eraseFile2 = new File(FileUtils.createDirectory(FILES_DIRECTORY), ERASE_FILE2);
		FileUtils.fillFile(eraseFile2, "Erase file 2");
		eraseFilePath2 = eraseFile2.getPath();
    }

    @Benchmark
    public int deleteFirstFileTest() {
    	
    	try {
			@SuppressWarnings("unused")
			final boolean fileDeleted = FileEraser.eraseFile(eraseFilePath1, OverwriteMode.SIMPLE_MODE);
		} catch (EraseException e) {
			e.printStackTrace();
		}

        return 0x0;
    }
    
    @Benchmark
    public int eraseFileSimpleModeTest() {
    	try {
			@SuppressWarnings("unused")
			final boolean fileDeleted = FileEraser.eraseFile(eraseFilePath1, OverwriteMode.SIMPLE_MODE);
		} catch (EraseException e) {
			e.printStackTrace();
		}

        return 0x0;
    }
    
    @Benchmark
    public int deleteSecondFileTest() {
    	
    	try {
			@SuppressWarnings("unused")
			final boolean fileDeleted = FileEraser.eraseFile(eraseFilePath2, OverwriteMode.SIMPLE_MODE);
		} catch (EraseException e) {
			e.printStackTrace();
		}

        return 0x0;
    }
    
    @Benchmark
    public int eraseFileOpenBsdModeTest() {
    	try {
			@SuppressWarnings("unused")
			final boolean fileDeleted = FileEraser.eraseFile(eraseFilePath2, OverwriteMode.OPENBSD_MODE);
		} catch (EraseException e) {
			e.printStackTrace();
		}

        return 0x0;
    }
	
	public static void main(String[] args) throws Exception {
		final Options options = new OptionsBuilder()
                .include(FileEraserBenchmark.class.getSimpleName())
                .forks(1)
                .build();

        new Runner(options).run();
    }
}

