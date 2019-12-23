package medical.com.medicalApplication.model;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;
import medical.com.medicalApplication.model.Medication;

public class TestMedication {
	private Medication medication;
	@Before
	public void before() {
		this.medication = new Medication("Med1","11/10/2001","04/06/2016","10ML/Day");
	}

	@Test
	public void testSetName() {
		assertTrue(medication.getName().equals("Med1"));
	}

	@Test
	public void testSetStartDate() {
		assertTrue(medication.getStartDate().equals("11/10/2001"));
	}

	@Test
	public void testSetEndDate() {
		assertTrue(medication.getEndDate().equals("04/06/2016"));
	}
	@Test
	public void testSetDose() {
		assertTrue(medication.getDose().equals("10ML/Day"));
	}

	@Test
	public void testToString() {
		String expected ="Medication:Med1 Start Date: 11/10/2001 End Date: 04/06/2016 Dose: 10ML/Day";
		assertEquals(expected, medication.toString());
	}

}
