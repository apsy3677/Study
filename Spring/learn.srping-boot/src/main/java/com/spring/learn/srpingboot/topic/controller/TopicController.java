package com.spring.learn.srpingboot.topic.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.Arrays;
import java.util.List;

@RestController
public class TopicController {

    @Autowired
    private TopicService topicService; // if instance is required @Autowired will look for already existing service that is instantied

    @GetMapping("/topics")
    public List<Topic> getAllTopics(){

        return topicService.getAllTopics();
    }

    @RequestMapping("/topics/{id}") // {id} is a variable portion send {id} to send String id
    public Topic getTopic(@PathVariable String id){
        return topicService.getTopic(id);
    }

    @RequestMapping(method = RequestMethod.POST, value = "/topics")
    public void addTopic(@RequestBody Topic topic){
        // get the body and convert it into topic
        topicService.addTopic(topic);
    }

    @RequestMapping(method = RequestMethod.PUT, value = "/topics/{id}")
    public void updateTopic(@RequestBody Topic topic, @PathVariable String id){
        // get the body and convert it into topic
        topicService.updateTopic(id, topic);
    }

    @RequestMapping(method = RequestMethod.DELETE, value = "/topics/{id}")
    public void deleteTopic(@RequestBody Topic topic, @PathVariable String id){
        // get the body and convert it into topic
        topicService.deleteTopic(id, topic);
    }
}
