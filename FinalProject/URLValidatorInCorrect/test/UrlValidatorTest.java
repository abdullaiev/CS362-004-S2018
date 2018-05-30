import junit.framework.TestCase;


public class UrlValidatorTest extends TestCase {
    public UrlValidatorTest(String testName) {
        super(testName);
    }


    public void testManualTest() {
        UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        assertTrue(validator.isValid("http://www.google.com"));
        assertFalse(validator.isValid("http://www.google.com//"));
        assertTrue(validator.isValid("https://www.google.com")); //---------------------EXCEPTION
        assertFalse(validator.isValid("htttps://www.google.com"));//--------------------EXCEPTION
        assertTrue(validator.isValid("http://www.google.org/"));
        assertFalse(validator.isValid("http//www.google.org/"));
        assertTrue(validator.isValid("http://www.google.org:8080"));  //----------------FAILING
        assertTrue(validator.isValid("http://www.google.com:65535/t123")); //-----------FAILING
        assertFalse(validator.isValid("http://www.google.org:118080"));
        assertTrue(validator.isValid("ftp://osu.edu")); //------------------------------EXCEPTION
        assertTrue(validator.isValid("http://qwerty.ua/asdf?param=test"));
        assertTrue(validator.isValid("http://qwerty.ua/zxcv?param=test2&another-param=123456"));
        assertTrue(validator.isValid("http://http.xyz/"));
        assertTrue(validator.isValid("http://com.http"));
    }

    public void testYourFirstPartition() {
    	UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        //testing valid and invalid URL Schemes
        String[] goodSchemes = {"", "h://", "http://", "f5p://", "f-.+p://", "ftttttttttp://"};
        String[] badSchemes = {"://", "3ttp://", "f$p://", "h:", "h//", "h:/"};
        int i;
        for (i = 0; i < goodSchemes.length; i++){
            StringBuilder tester = new StringBuilder();
            tester.append(goodSchemes[i]);
            tester.append("www.google.com");
            String buffer = tester.toString();
            System.out.println(buffer);
            assertTrue(validator.isValid(buffer));
        }
        for (i = 0; i < badSchemes.length; i++){
        	StringBuilder tester = new StringBuilder();
            tester.append(badSchemes[i]);
            tester.append("www.google.com");
            String buffer = tester.toString();
            System.out.println(buffer);
            assertFalse(validator.isValid(buffer));
        }


    }

    public void testYourSecondPartition() {
        UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
         //testing valid and invalid URL authoirities
        String[] goodAuth = {"www.google.com", "w.google.com", "google.com", "g00gle.com", "g.com", "google.ca", "0.0.0.0", "1.1.1.1", "255.255.255.255" };
        String[] badAuth = { "", "www..com", ".com", "google.", "g$$gle.com", "256.256.256.256", "0.0.0", "0.0.0.0.0", ".0.0.0.0", "0.0.0.0.", "-1.-1.-1.-1" };
        int i;
        for (i = 0; i < goodAuth.length; i++){
            StringBuilder tester = new StringBuilder();
            tester.append("http://");
            tester.append(goodAuth[i]);
            String buffer = tester.toString();
            System.out.println(buffer);
            assertTrue(validator.isValid(buffer));
        }
        for (i = 0; i < badAuth.length; i++){
        	 StringBuilder tester = new StringBuilder();
             tester.append("http://");
             tester.append(badAuth[i]);
             String buffer = tester.toString();
             System.out.println(buffer);
             assertFalse(validator.isValid(buffer));
        }

    }
    
    
    public void testYourThirdPartition() {
        UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
              //testing valid and invalid URL ports
        String[] goodPort = {"", ":0", ":1", ":80", ":65535" };
        String[] badPort = {":65536", ":-1", ":1a", ":a" };
        int i;
        for (i = 0; i < goodPort.length; i++){
            StringBuilder tester = new StringBuilder();
            tester.append("http://www.google.com");
            tester.append(goodPort[i]);
            String buffer = tester.toString();
            System.out.println(buffer);
            assertTrue(validator.isValid(buffer));
        }
        for (i = 0; i < badPort.length; i++){
        	StringBuilder tester = new StringBuilder();
            tester.append("http://www.google.com");
            tester.append(badPort[i]);
            String buffer = tester.toString();
            System.out.println(buffer);
            assertFalse(validator.isValid(buffer));
        }
    }
    
    public void testYourFourthPartition() {
    	
      
//          testIsValid(testUrlPartsOptions, options);
        UrlValidator validator = new UrlValidator(null, null, (UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS));
              //testing valid and invalid URL paths
        String[] goodPath = {"", "/valid","/v1%", "/111", "/&&&"};
        String[] badPath = {"//invalid", "/this//alsoinvalid", "/not:good/", };
        int i;
        for (i = 0; i < goodPath.length; i++){
        	 StringBuilder tester = new StringBuilder();
             tester.append("http://www.google.com");
             tester.append(goodPath[i]);
             String buffer = tester.toString();
             System.out.println(buffer);
             assertTrue(validator.isValid(buffer));
        }
        for (i = 0; i < badPath.length; i++){
        	StringBuilder tester = new StringBuilder();
            tester.append("http://www.google.com");
            tester.append(badPath[i]);
            String buffer = tester.toString();
            System.out.println(buffer);
            assertFalse(validator.isValid(buffer));
        }
    }
    
    public void testYourFifthPartition() {
        UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
               //testing valid and invalid URL query
        String[] goodQ = { "", "?this=good", "?this=good&sois=this", "?this=good;sois=this", "?works=this+thing+works" };

        int i;
        for (i = 0; i < goodQ.length; i++){
        	 StringBuilder tester = new StringBuilder();
             tester.append("http://www.google.com");
             tester.append(goodQ[i]);
             String buffer = tester.toString();
             System.out.println(buffer);
             assertTrue(validator.isValid(buffer));
        }
        
    }

    public void testIsValid() {
        //You can use this function for programming based testing
    	
    	UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
    	
    	//Create string from arrays of query parts
    	ResultPair[] urlArr = {
    			new ResultPair("http://", true),
    			new ResultPair("https://", true),
    			new ResultPair("ftp://", true),
    			new ResultPair("", true),
    			new ResultPair("gibberish://", false),
    			new ResultPair("/", false),
    			new ResultPair(":", false)
    	};
    	
    	ResultPair[] authorityArr = {
    			new ResultPair("www.google.com", true),
    			new ResultPair("google.com", true),
    			new ResultPair("www.usa.gov", true),
    			new ResultPair("usa.gov", true),
    			new ResultPair("www.wordpress.org", true),
    			new ResultPair("wordpress.org", true),
    			new ResultPair("255.255.255.0", true),
    			new ResultPair("www.google.co.uk", true),
    			new ResultPair("www.google.co.uk", true),
    			new ResultPair("developer.amazon.com", true),
    			new ResultPair(".www.google.com", false),
    			new ResultPair("www.google.com.", false),
    			new ResultPair("singleword", false),
    			new ResultPair("", false),
    			new ResultPair("256.0.0.0", false),
    			new ResultPair("0.0.0.256", false),
    			new ResultPair("128.12.46.5.15", false),
    	};
    	
    	ResultPair[] portArr = {
    			new ResultPair(":656", true),
    			new ResultPair(":0", true),
    			new ResultPair(":65535", true),
    			new ResultPair("", true),
    			new ResultPair(":-1", false),
    			new ResultPair(":65636", false),
    			new ResultPair(":word", false),
    			new ResultPair("word", false)
    	};
    	
    	ResultPair [] pathArr = {
    			new ResultPair("", true),
    			new ResultPair("/word", true),
                new ResultPair("/12345", true),
                new ResultPair("/~", true),
                new ResultPair("/word/12345", true),
                new ResultPair("/word/12345/test123", true),
                new ResultPair("noslash", false),
                new ResultPair("//", false),
                new ResultPair("/word/", true),
                new ResultPair("/validstart//", false)
    	};
    	
    	// Iterate over all permutations of strings
    	int[] position = new int[]{0, 0, 0, 0};
    	int failed = 0;
    	int i = 0;
    	int tests = urlArr.length * authorityArr.length * portArr.length * pathArr.length;
    	
    	while(true) {
    		
    		// Update position counters
    		position[0]++;
    		if (i % (urlArr.length) == 0) {
    			position[0] = 0;
    			position[1]++;
    		}
    		if (i % (urlArr.length * authorityArr.length) == 0) {
    			position[0] = 0;
    			position[1] = 0;
    			position[2]++;
    		}
    		if (i % (urlArr.length * authorityArr.length * portArr.length) == 0) {
    			position[0] = 0;
    			position[1] = 0;
    			position[2] = 0;
    			position[3]++;
    			
    			if (position[3] >= pathArr.length) break;
    		}
    		
    		// Build the strings
    		StringBuilder testUrl = new StringBuilder();
    		testUrl.append(urlArr[position[0]].item);
    		testUrl.append(authorityArr[position[1]].item);
    		testUrl.append(portArr[position[2]].item);
    		testUrl.append(pathArr[position[3]].item);
    		String url = testUrl.toString();
    		
    		// Get expected results based on test parts
    		boolean expected = urlArr[position[0]].valid && authorityArr[position[1]].valid && portArr[position[2]].valid && pathArr[position[3]].valid;
    		// Get result from isValid
    		boolean result = validator.isValid(url);
    		
    		// Print test results
    		if (expected != result) {
    			System.out.println("FAILED: " + url);
    			failed++;
    		} else {
    			System.out.println("SUCCESS: " + url);
    		}
    		i++;
    	}
    	System.out.println("RESULTS: " + failed + " of " + tests + " failed.");
    }
}

