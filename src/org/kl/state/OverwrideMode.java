package org.kl.state;

public enum OverwrideMode {
	SIMPLE_MODE(1),
	DOE_MODE(3),
	OPENBSD_MODE(3),
	RCMP_MODE(3),
	DOD_MODE(7),
	GUTMAN_MODE(35);
	
	private int number;
	
	private OverwrideMode(int number) {
		this.number = number;
	}
	
	public int getNumber() {
		return number;
	}
}
