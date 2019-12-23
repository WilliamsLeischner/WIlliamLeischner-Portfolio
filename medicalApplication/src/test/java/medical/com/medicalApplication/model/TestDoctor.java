package medical.com.medicalApplication.model;

import static org.junit.Assert.*;
import org.junit.Before;
import org.junit.Test;
import medical.com.medicalApplication.model.Doctor;

public class TestDoctor {
	private Doctor doctor;
	
	@Before
	public void before() {
		this.doctor = new Doctor("Loveless", "1234");
	}


	@Test
	public void testSetName() {
		assertTrue(doctor.getName().equals("Loveless"));
	}


	@Test
	public void testSetId() {
		assertTrue(doctor.getId().equals("1234"));
	}

	@Test
	public void testToString() {
		String expected ="Doctor Name:Loveless ID: 1234";
		assertEquals(expected, doctor.toString());
	}

}
