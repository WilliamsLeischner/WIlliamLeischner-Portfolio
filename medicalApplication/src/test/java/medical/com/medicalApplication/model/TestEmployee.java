package medical.com.medicalApplication.model;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import medical.com.medicalApplication.model.Employee;

public class TestEmployee {
	private Employee employee;
	@Before
	public void before() {
		this.employee= new Employee("Brown Nose", "1111");
	}
	@Test
	public void testSetName() {
		assertTrue(employee.getName().equals("Brown Nose"));
	}
	
	@Test
	public void testSetId() {
		assertTrue(employee.getId().equals("1111"));
	}

	@Test
	public void testSetPassword() {
		assertTrue(employee.getPassword().equals("Open"));
	}

}
