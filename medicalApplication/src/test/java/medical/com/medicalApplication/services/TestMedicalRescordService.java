package medical.com.medicalApplication.services;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import medical.com.medicalApplication.services.MedicalRescordService;
import medical.com.medicalApplication.model.Patient;
import medical.com.medicalApplication.model.PatientHistory;
import medical.com.medicalApplication.model.MedicalRecord;


public class TestMedicalRescordService {
	private Patient patient;
	private MedicalRecord medicalRecord;
	private PatientHistory history;
	private MedicalRescordService mSR;

	@Before
	public void setUp() throws Exception {
		MedicalRescordService.getReference().addPatient("Sicko","2222");
		this.patient = MedicalRescordService.getReference().getPatient("2222");
		this.medicalRecord = MedicalRescordService.getReference().getMedicalRecord("2222");
		this.history =medicalRecord.getHistory();
	}
	
	@Test
	public void testAddPatient() {
		assertTrue(patient.getName().equals("Sicko"));
	}
	@Test
	public void testGetPatientsWithAllergies() {
		assertNotNull(mSR.getPatientsWithAllergies("Food"));

	}
	
	@Test
	public void testGetMedicalRecord() {
		assertTrue(medicalRecord.getPatient().equals(patient));
	}
	@Test
	public void testGetAllPatients() {
		assertNotNull(MedicalRescordService.getReference().getAllPatients());
	}

}
