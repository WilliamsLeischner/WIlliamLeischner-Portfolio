package medical.com.medicalApplication.model;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import medical.com.medicalApplication.model.Allergey;


public class TestAllergey {
	private Allergey allergey;
	@Before
	public void before() {
		this.allergey = new Allergey("Food");
	}


	

	@Test
	public void testSetName() {
		assertTrue(allergey.getName().equals("Food"));
	}
	@Test
	public void testToString() {
		String expected="Allergy Food";
		assertEquals(expected, allergey.toString());
	}

}
