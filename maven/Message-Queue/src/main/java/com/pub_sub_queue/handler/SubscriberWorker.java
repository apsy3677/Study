package com.pub_sub_queue.handler;

import com.pub_sub_queue.model.Message;
import com.pub_sub_queue.model.Topic;
import com.pub_sub_queue.model.TopicSubscriber;
import lombok.Getter;
import lombok.NonNull;
import lombok.SneakyThrows;

@Getter
public class SubscriberWorker implements Runnable{
    private final Topic topic;
    private final TopicSubscriber topicSubscriber;

    public SubscriberWorker(@NonNull Topic topic, @NonNull TopicSubscriber topicSubscriber) {

        this.topic = topic;
        this.topicSubscriber = topicSubscriber;
    }

    @SneakyThrows
    @Override
    public void run() {
        synchronized (topicSubscriber){
            do{
                int currOffset = topicSubscriber.getOffset().get();

                while(currOffset >= topic.getMessages().size()){
                    topicSubscriber.wait(); // thread will go to sleep
                }

                Message message = topic.getMessages().get(currOffset);
                topicSubscriber.getSubscriber().consume(message);

                topicSubscriber.getOffset().compareAndSet(currOffset, currOffset+1);

            }while(true);
        }
    }

    public void wakeupIfNeeded(){
        synchronized (topicSubscriber){
            topicSubscriber.notify();
        }
    }
}
