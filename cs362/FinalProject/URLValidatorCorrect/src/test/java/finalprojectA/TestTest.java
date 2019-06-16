package finalprojectA;

import junit.framework.TestCase;

public class TestTest extends TestCase {
    public void testManualTest()
    {
    //You can use this function to implement your manual testing
        UrlValidator urlVal = new UrlValidator();
        assertTrue(urlVal.isValid("http://www.google.com"));
        assertTrue(urlVal.isValid("http://www.google.com:0/../"));
    }
}
