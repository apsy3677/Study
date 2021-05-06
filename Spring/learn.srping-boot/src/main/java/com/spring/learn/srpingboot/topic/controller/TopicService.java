package com.spring.learn.srpingboot.topic.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

@Service
public class TopicService {
    // @service
    // business services are typically singleton
    // spring creates this instance
    // creates a service and registers it

    @Autowired
    private TopicRepository topicRepository;

    List<Topic> topics = new ArrayList<>(Arrays.asList(
            new Topic("spring0", "spring framework", "spring framework desc"),
                new Topic("spring1", "spring framework1", "spring framework desc"),
                new Topic("spring2", "spring framework2", "spring framework desc"),
                new Topic("spring3", "spring framework3", "spring framework desc")

        ));

    public List<Topic> getAllTopics(){
        return topics;
    }

    public Topic getTopic(String id) {
        return topics.stream().filter(topic -> {
           return topic.getId().equals(id);
        }).findFirst().get();
    }

    public void addTopic(Topic topic) {
        topics.add(topic);
    }

    public void updateTopic(String id, Topic topic) {
        for(int i=0;i<topics.size();i++){
            Topic t = topics.get(i);
            if(t.getId().equals(id)){
                topics.set(i, topic);
                return;
            }
        }
    }

    public void deleteTopic(String id, Topic topic) {
//        for(int i=0;i<topics.size();i++){
//            Topic t = topics.get(i);
//            if(t.getId().equals(id)){
//                topics.remove(i);
//                return;
//            }
//        }
        topics.removeIf(t-> t.getId().equals(id));
    }
}
