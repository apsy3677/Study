package com.spring.learn.srpingboot.topic.controller;

import org.springframework.data.repository.CrudRepository;

public interface TopicRepository extends CrudRepository<Topic, String> {

    //getAllTopics()
    //getTopic(String id)
    //updateTopic(Topic t)
    //deleteTopic(String id)

    // JPA will create these classes

//    CrudRepository comes already in the
}
