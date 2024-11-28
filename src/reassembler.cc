#include "reassembler.hh"

using namespace std;

void Reassembler::insert(uint64_t first_index, string data, bool is_last_substring)
{
    uint64_t wd_start = nxt_index;
    uint64_t wd_end = wd_start + output_.writer().available_capacity();
    uint64_t cur_start = first_index;
    uint64_t cur_end = cur_start + data.size();
    uint64_t available_capacity = output_.writer().available_capacity();

    // Detects whether the byte stream is closed
    if (output_.writer().is_closed() || available_capacity == 0) {
        return;
    }

    if (is_last_substring) {
        eof_idx = cur_end;
    }

    if (cur_start >= wd_end) {
        return;
    }

    // Adjust window boundaries
    uint64_t start_idx = max(wd_start, cur_start);
    uint64_t end_idx = min(wd_end, cur_end);
    if (start_idx >= end_idx) {
        if (nxt_index == eof_idx) {
            output_.writer().close();
        }
        return;
    }

    uint64_t len = end_idx - start_idx;
    reBuffer.insert({start_idx, end_idx, data.substr(start_idx - first_index, len)});

    // Handle the overlapping intervals
    std::vector<Interval> merge; // merge vector
    auto it = reBuffer.begin();
    Interval last = *it;
    ++it;
    
    while (it != reBuffer.end()) {
        if (it->first_index <= last.end_index) {
            if (last.end_index <= it->end_index) {
                last.end_index = it->end_index;
                last.data = last.data.substr(0, it->first_index - last.first_index)+it->data;
            }
        } else {
            merge.push_back(last);
            last = *it;
        }
        ++it;
    }
    merge.push_back(last);

    reBuffer.clear();
    for (const auto& interval : merge) {
        reBuffer.insert(interval);
    }

    // Push the intervals into the byte stream
    it = reBuffer.begin();
    while (it != reBuffer.end() && it->first_index == nxt_index) {
        output_.writer().push(it->data);
        nxt_index = it->end_index;
        it = reBuffer.erase(it);  // Ensure that the iterator is valid after erase
    }

    if (nxt_index == eof_idx) {
        output_.writer().close();
    }
}

uint64_t Reassembler::bytes_pending() const
{
    uint64_t pending = 0;
    if (reBuffer.empty()) {
        return pending;
    }

    for (const auto& interval : reBuffer) {
        pending += interval.end_index - interval.first_index;
    }

    return pending;
}
