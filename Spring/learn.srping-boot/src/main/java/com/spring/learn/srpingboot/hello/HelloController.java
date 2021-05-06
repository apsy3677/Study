package com.spring.learn.srpingboot.hello;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class HelloController {

    @RequestMapping("/hello") // only for get
    public String sayHi(){
        return "Hi !";
    }
}
