void				init_rec_queue(t_trace_record_queue *rec_queue)
{
	rec_queue->count = 0;
	rec_queue->front = 0;
	rec_queue->rear = -1;
}

int					is_rec_queue_full(t_trace_record_queue *rec_queue)
{
	return (rec_queue->count == RT_MAX_RECORD);
}

int					is_rec_queue_empty(t_trace_record_queue *rec_queue)
{
	return (rec_queue->count == 0);
}

void				push_rec_queue(
	t_trace_record_queue *rec_queue,
	t_trace_record rec
)
{
	if (is_rec_queue_full(rec_queue))
		return ;
	if (rec_queue->rear == RT_MAX_RECORD - 1)
		rec_queue->rear = 0;
	rec_queue->rear += 1;
	rec_queue->queue[rec_queue->rear] = rec;
	rec_queue->count += 1;
}

t_trace_record		*pop_rec_queue(t_trace_record_queue *rec_queue)
{
	t_trace_record		*poped;

	poped = &(rec_queue->queue[rec_queue->front]);
	rec_queue->front += 1;
	if (rec_queue->front == RT_MAX_RECORD)
		rec_queue->front = 0;
	rec_queue->count -= 1;
	return (poped);
}