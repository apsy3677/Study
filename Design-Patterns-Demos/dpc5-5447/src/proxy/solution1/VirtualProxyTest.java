/*
 * This class forms part of the Design Patterns Course by
 * Dr Heinz Kabutz from JavaSpecialists.eu and may not be
 * distributed without written consent.
 *
 * Copyright 2001-2018, Heinz Kabutz, All rights reserved.
 */
package proxy.solution1;

import org.junit.*;
import util.*;

import java.lang.reflect.*;

import static org.junit.Assert.*;

//DON'T CHANGE
public class VirtualProxyTest {
    public static final Class<?> LUTEFISK_CLASS;

    static {
        try {
            char[] lutefiskName = {'L', 'u', 't', 'e', 'f', 'i', 's', 'k'};
            LUTEFISK_CLASS = ClassHelper.getClass(new String(lutefiskName));
        } catch (ClassNotFoundException e) {
            throw new Error(e);
        }
    }

    @Test
    public void testLutefiskIsInterface() throws IllegalAccessException, InstantiationException {
        assertTrue("We need to convert Lutefisk into an interface, it is our 'Subject'", LUTEFISK_CLASS.isInterface());
    }

    @Test
    public void testScandinaviansHaveReferenceToVirtualLutefisk() throws IllegalAccessException, InstantiationException {
        Class<?> virtualLutefiskClass = findVirtualLutefiskClass();
        for (Field field : Swede.class.getDeclaredFields()) {
            if (field.getType().isAssignableFrom(LUTEFISK_CLASS)) {
                field.setAccessible(true);
                assertTrue("lutefisk field in Swede should be assigned to a VirtualLutefisk",
                    virtualLutefiskClass.isInstance(field.get(new Swede())));
            }
        }
        for (Field field : Norwegian.class.getDeclaredFields()) {
            if (field.getType().isAssignableFrom(LUTEFISK_CLASS)) {
                field.setAccessible(true);
                assertTrue("lutefisk field in Norwegian should be assigned to a VirtualLutefisk",
                    virtualLutefiskClass.isInstance(field.get(new Norwegian())));
            }
        }
    }

    @Test
    public void testScandinaviansHaveNonNullReferenceToVirtualLutefisk() throws IllegalAccessException, InstantiationException {
        Class<?> virtualLutefiskClass = findVirtualLutefiskClass();
        for (Field field : Swede.class.getDeclaredFields()) {
            if (field.getType().isAssignableFrom(LUTEFISK_CLASS)) {
                field.setAccessible(true);
                assertTrue("lutefisk field in Swede should be assigned to a VirtualLutefisk",
                    virtualLutefiskClass.isInstance(field.get(new Swede())));
            }
        }
        for (Field field : Norwegian.class.getDeclaredFields()) {
            if (field.getType().isAssignableFrom(LUTEFISK_CLASS)) {
                field.setAccessible(true);
                assertTrue("lutefisk field in Norwegian should be assigned to a VirtualLutefisk",
                    virtualLutefiskClass.isInstance(field.get(new Norwegian())));
            }
        }
    }

    @Test
    public void testRealLutefiskClassExists() throws Exception {
        try {
            Class<?> realLutefiskClass =
                ClassHelper.getClass("RealLutefisk").asSubclass(LUTEFISK_CLASS);
            Object realLutefisk = realLutefiskClass.getConstructor().newInstance();
            eat(realLutefisk);
        } catch (ClassCastException e) {
            fail("The RealLutefisk should be derived from Lutefisk");
        } catch (ClassNotFoundException e) {
            fail("We need a RealLutefisk class that contains the original Lutefisk code");
        }
    }

    private void eat(Object realLutefisk) throws ReflectiveOperationException {
        LUTEFISK_CLASS.getMethod("eat").invoke(realLutefisk);
    }

    @Test
    public void testVirtualLutefiskClassExists() throws Exception {
        try {
            Class<?> virtualLutefiskClass = findVirtualLutefiskClass();
            Object virtualLutefisk = virtualLutefiskClass.getConstructor().newInstance();
            assertEquals("Virtual Lutefisk should only have one field, the delegate", 1, virtualLutefiskClass.getDeclaredFields().length);
            Field delegate = virtualLutefiskClass.getDeclaredFields()[0];
            assertTrue("Delegate should be of type Lutefisk", delegate.getType().isAssignableFrom(LUTEFISK_CLASS));
            delegate.setAccessible(true);
            assertNull("Initially the delegate field should be null", delegate.get(virtualLutefisk));
            eat(virtualLutefisk);
            assertNotNull("After calling eat(), the delegate field should NOT be null", delegate.get(virtualLutefisk));
        } catch (ClassCastException e) {
            fail("The VirtualLutefisk should be derived from Lutefisk");
        }
    }

    private Class<?> findVirtualLutefiskClass() {
        try {
            return ClassHelper.getClass("VirtualLutefisk").asSubclass(LUTEFISK_CLASS);
        } catch (ClassNotFoundException e) {
            fail("We need a VirtualLutefisk that constructs the real lutefisk on demand");
            return null; // will never be called.
        }
    }
}
