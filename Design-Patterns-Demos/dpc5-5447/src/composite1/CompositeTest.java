/*
 * This class forms part of the Design Patterns Course by
 * Dr Heinz Kabutz from JavaSpecialists.eu and may not be
 * distributed without written consent.
 *
 * Copyright 2001-2020, Heinz Kabutz, All rights reserved.
 */

package composite1;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class CompositeTest {
    @Test
    public void testConstant(){
        double testValue = 3.0;
        Expression e = new Constant(testValue);
        assertEquals(testValue, e.getValue(),0.0);
    }

    @Test
    public void testAdder(){
        double testVal1 = 1.0;
        double testVal2 = 2.0;
        Expression left = new Constant(testVal1);
        Expression right = new Constant(testVal2);
        Expression e = new Adder (left, right);
        assertEquals(testVal1 + testVal2, e.getValue(), 0.0);
    }

    @Test
    public void testSubtractor(){
        double testVal1 = 1.0;
        double testVal2 = 2.0;
        Expression left = new Constant(testVal1);
        Expression right = new Constant(testVal2);
        Expression e = new Subtractor (left, right);
        assertEquals(testVal1 - testVal2, e.getValue(), 0.0);
    }
}
