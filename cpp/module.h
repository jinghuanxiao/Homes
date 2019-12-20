#pragma once

#define CACHE_QUEUE_MAX_SIZE 800

template<typename Type> struct _CacheNodeElement
{
	Type entryTime;
};

template<typename Type> struct _CacheNode {
	// ����
	Type * data;
	// ��һ��
	struct _CacheNode* next;
};
// ����

template<typename Type> struct _CacheQueue {
	// ��С
	int size;
	// ����ͷ
	Type * head;
	// ����β
	Type * tail;
	// �Ƿ�����
	bool is_block;
	// �߳���
	pthread_mutex_t* mutex_id;
	// �߳���������
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
* ���ٶ���
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
* �ж��Ƿ�Ϊ��
* @param queue
* @return
*/
template<typename Type>
bool queueIsEmpty(Type* queue) {
	return queue->size == 0;
}

/**
* �ж��Ƿ�����
* @param queue
* @return
*/
template<typename Type>
bool queueIsFull(Type* queue) {
	return queue->size == CACHE_QUEUE_MAX_SIZE;
}

/**
* ��� (����)
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
* ���� (����)
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
* ��ն���
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
* �������
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