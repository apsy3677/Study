package com.pub_sub_queue.model;

import com.pub_sub_queue.public_interfaces.ISubscriber;
import lombok.Getter;
import lombok.NonNull;

import java.util.ArrayList;
import java.util.List;

@Getter
public class Topic {
    private final String topicName;
    private final String topicId;
    private final List<Message> messages;  // TODO : make it immutable and send it outside
    private final List<TopicSubscriber> subscribers; // TODO : make it immutable and send it outside

    public Topic(String topicName, String topicId) {
        this.topicName = topicName;
        this.topicId = topicId;
        this.messages = new ArrayList<>();
        this.subscribers = new ArrayList<>();
    }

    public synchronized void addMessage(@NonNull final Message message){
        messages.add(message);
    }

    public void addSubscriber(@NonNull final TopicSubscriber topicSubscriber ){
        subscribers.add(topicSubscriber);
    }
}
