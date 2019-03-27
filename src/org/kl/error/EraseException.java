package org.kl.error;

public class EraseException extends Exception {
	private static final long serialVersionUID = 1L;
	private String message;

	public EraseException(String message) {
		super();
		this.message = message;
	}
	
	@Override
	public String getMessage() {
		return message;
	}
}
