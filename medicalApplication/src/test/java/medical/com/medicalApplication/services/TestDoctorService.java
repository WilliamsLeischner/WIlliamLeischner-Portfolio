package medical.com.medicalApplication.services;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;


import medical.com.medicalApplication.model.Doctor;

public class TestDoctorService {
	private Doctor doctor;

	@Before
	public void setUp() throws Exception {
		DoctorService.getReference().addDoctor("Loveless", "1234");
		
	}
	
	@Test
	public void testAddDoctor() {
		assertTrue(doctor.getName().equals("Loveless"));
	}
	@Test
	public void testGetAllDoctorS() {
		assertNotNull(DoctorService.getReference().getAllDoctors());
	}
}
