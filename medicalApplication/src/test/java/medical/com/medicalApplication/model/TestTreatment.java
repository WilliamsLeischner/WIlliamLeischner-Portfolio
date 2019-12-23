package medical.com.medicalApplication.model;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import medical.com.medicalApplication.model.Treatment;

public class TestTreatment {
	private Treatment treatment;
	
	@Before
	public void before() {
		this.treatment = new Treatment("03/07/2014","Ulcer", "Ulcer in Stomach");
	}

	@Test
	public void testSetDiagnose() {
		assertTrue(treatment.getDiagnose().equals("Ulcer"));
	}

	@Test
	public void testTreatmentDate() {
		assertTrue(treatment.getTreatmentDate().equals("03/07/2014"));
	}


	@Test
	public void testSetDescription() {
		assertTrue(treatment.getDescription().equals("Ulcer in Stomach"));
	}

	@Test
	public void testToString() {
		String expected = "Treatment:  Date: 03/07/2014 Diagnose: Ulcer";
		assertEquals(expected, treatment.toString());
	}

}
