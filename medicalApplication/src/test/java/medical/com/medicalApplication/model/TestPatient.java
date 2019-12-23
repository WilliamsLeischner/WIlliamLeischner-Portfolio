package medical.com.medicalApplication.model;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;
import medical.com.medicalApplication.model.Patient;

public class TestPatient {
	private Patient patient;
	@Before
	public void before() {
		this.patient = new Patient("Sicko", "2222");
	}

	@Test
	public void testSetName() {
		assertTrue(patient.getName().equals("Sicko"));
	}

	@Test
	public void testSetId() {
		assertTrue(patient.getId().equals("2222"));
	}

	@Test
	public void testToString() {
		String expected ="Patient Name: Sicko ID: 2222";
		assertEquals(expected, patient.toString());
	}

}
