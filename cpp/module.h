#pragma once

#define CACHE_QUEUE_MAX_SIZE 800

template<typename Type> struct _CacheNodeElement
{
	Type entryTime;
};

template<typename Type> struct _CacheNode {
	// 数据
	Type * data;
	// 下一个
	struct _CacheNode* next;
};
// 队列

template<typename Type> struct _CacheQueue {
	// 大小
	int size;
	// 队列头
	Type * head;
	// 队列尾
	Type * tail;
	// 是否阻塞
	bool is_block;
	// 线程锁
	pthread_mutex_t* mutex_id;
	// 线程条件变量
	pthread_cond_t* not_empty_condition;
	pthread_cond_t* not_full_condition;
};

template<typename Type>
void queueInit(Type * queue) {
	queue->size = 0;
	queue->head = NULL;
	queue->tail = NULL;
	queue->is_block = true;
	queue->mutex_id = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(queue->mutex_id, NULL);
	queue->not_empty_condition = (pthread_cond_t*)malloc(sizeof(pthread_cond_t));
	pthread_cond_init(queue->not_empty_condition, NULL);
	queue->not_full_condition = (pthread_cond_t*)malloc(sizeof(pthread_cond_t));
	pthread_cond_init(queue->not_full_condition, NULL);
}

/**
* 销毁队列
* @param queue
*/
template<typename Type, typename NodeType>
void queueDestroy(Type * queue) {
	NodeType* node = queue->head;
	while (node != NULL) {
		queue->head = queue->head->next;
		free(node);
		node = queue->head;
	}
	queue->head = NULL;
	queue->tail = NULL;
	queue->size = 0;
	queue->is_block = false;
	pthread_mutex_destroy(queue->mutex_id);
	pthread_cond_destroy(queue->not_empty_condition);
	pthread_cond_destroy(queue->not_full_condition);
	free(queue->mutex_id);
	free(queue->not_empty_condition);
	free(queue->not_full_condition);
}

/**
* 判断是否为空
* @param queue
* @return
*/
template<typename Type>
bool queueIsEmpty(Type* queue) {
	return queue->size == 0;
}

/**
* 判断是否已满
* @param queue
* @return
*/
template<typename Type>
bool queueIsFull(Type* queue) {
	return queue->size == CACHE_QUEUE_MAX_SIZE;
}

/**
* 入队 (阻塞)
* @param queue
* @param element
*/
template<typename Type,typename Nodetype>
void queueIn(Type* queue, Nodetype* node) {
	pthread_mutex_lock(queue->mutex_id);
	while (queueIsFull(queue) && queue->is_block) {
		pthread_cond_wait(queue->not_full_condition, queue->mutex_id);
	}
	if (queue->size >= CACHE_QUEUE_MAX_SIZE) {
		pthread_mutex_unlock(queue->mutex_id);
		return;
	}
	if (queue->tail == NULL) {
		queue->head = node;
		queue->tail = node;
	}
	else {
		queue->tail->next = node;
		queue->tail = node;
	}
	queue->size += 1;
	pthread_cond_signal(queue->not_empty_condition);
	pthread_mutex_unlock(queue->mutex_id);
}

/**
* 出队 (阻塞)
* @param queue
* @return
*/
template<typename Type, typename NodeType>
NodeType* queueOut(Type *queue) {
	pthread_mutex_lock(queue->mutex_id);
	while (queueIsEmpty(queue) && queue->is_block) {
		pthread_cond_wait(queue->not_empty_condition, queue->mutex_id);
	}
	if (queue->head == NULL) {
		pthread_mutex_unlock(queue->mutex_id);
		return NULL;
	}
	NodeType* node = queue->head;
	queue->head = queue->head->next;
	if (queue->head == NULL) {
		queue->tail = NULL;
	}
	queue->size -= 1;
	pthread_cond_signal(queue->not_full_condition);
	pthread_mutex_unlock(queue->mutex_id);
	return node;
}

/**
* 清空队列
* @param queue
*/
template<typename Type, typename NodeType>
void queueClear(Type * queue) {
	pthread_mutex_lock(queue->mutex_id);
	NodeType* node = queue->head;
	while (node != NULL) {
		queue->head = queue->head->next;
		free(node);
		node = queue->head;
	}
	queue->head = NULL;
	queue->tail = NULL;
	queue->size = 0;
	queue->is_block = true;
	pthread_cond_signal(queue->not_full_condition);
	pthread_mutex_unlock(queue->mutex_id);
}

/**
* 打断阻塞
* @param queue
*/
template<typename Type>
void breakBlock(Type* queue) {
	if (queue == NULL) {
		return;
	}
	queue->is_block = false;
	pthread_cond_signal(queue->not_empty_condition);
	pthread_cond_signal(queue->not_full_condition);
}