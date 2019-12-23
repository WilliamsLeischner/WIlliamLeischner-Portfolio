package medical.com.medicalApplication.model;

import static org.junit.Assert.*;

import java.util.ArrayList;
import java.util.List;

import org.junit.Before;
import org.junit.Test;

import medical.com.medicalApplication.model.Medication;
import medical.com.medicalApplication.model.Allergey;
import medical.com.medicalApplication.model.Treatment;
import medical.com.medicalApplication.model.PatientHistory;

public class TestPatientHistory {
	private PatientHistory history;
	private List<Treatment> treatments;
	private List<Medication> medications;
	private List<Allergey> allergy;
	
	@Before
	public void before() {
		this.history = new PatientHistory();
		this.treatments = new ArrayList<Treatment>();
		this.medications = new ArrayList<Medication>();
		this.allergy = new ArrayList<Allergey>();
		treatments.add(new Treatment("03/07/2014","Ulcer", "Ulcer in Stomach"));
		treatments.add(new Treatment("04/05/2015", "Flu", "Avion Flu"));
		medications.add(new Medication("Med1","11/10/2001","04/06/2016","10ML/Day"));
		medications.add(new Medication("Med2","10/10/2010","01/10/2011","1 Tablet/Day"));
		allergy.add(new Allergey("Food"));
		allergy.add(new Allergey("Pollen"));
	}

	@Test
	public void testAddTreatment() {
			history.addTreatment(new Treatment("03/07/2014","Ulcer", "Ulcer in Stomach"));	
			assertTrue(history.getAllTreatments().stream().anyMatch(treatment-> treatment.getTreatmentDate().equals("03/07/2014") && treatment.getDiagnose().equals("Ulcer") && treatment.getDescription().equals("Ulcer in Stomach")));

	}

	@Test
	public void testAddAllergy() {
		history.addAllergy(new Allergey("Food"));	
		assertTrue(history.getAlergies().stream().anyMatch(allergey-> allergey.getName().equals("Food")));

}
	

	@Test
	public void testAddMedication() {
		history.addMedication(new Medication("Med1","11/10/2001","04/06/2016","10ML/Day"));	
		assertTrue(history.getAllMedications().stream().anyMatch(medication-> medication.getName().equals("Med1") && medication.getStartDate().equals("11/10/2001") && medication.getEndDate().equals("04/06/2016") && medication.getDose().equals("10ML/Day")));
	}

}
