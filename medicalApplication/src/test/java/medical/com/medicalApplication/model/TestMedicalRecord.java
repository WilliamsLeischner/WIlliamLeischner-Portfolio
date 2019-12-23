package medical.com.medicalApplication.model;

import static org.junit.Assert.*;
import org.junit.Before;
import org.junit.Test;

import medical.com.medicalApplication.model.MedicalRecord;


public class TestMedicalRecord {
	private MedicalRecord medicalRecord;
	private Patient patient;
	private PatientHistory history;
	@Before
	public void before() {
		this.patient = new Patient("Sicko", "2222");
		this.medicalRecord= new MedicalRecord(patient);
		this.history = new PatientHistory();
	}

	@Test
	public void testGetPatient() {
		assertTrue(medicalRecord.getPatient().equals(patient));
	}

	@Test
	public void testGetHistory() {
		assertTrue(medicalRecord.getHistory().equals(history));
	}

}
