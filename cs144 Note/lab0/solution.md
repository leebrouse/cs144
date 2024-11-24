# Lab0: Reliable byte stream
 At First ,let we see the member variable in my solution
 ## byte_stream.hh
 ```
class ByteStream
{
public:
  explicit ByteStream( uint64_t capacity );

  // Helper functions (provided) to access the ByteStream's Reader and Writer interfaces
  Reader& reader();
  const Reader& reader() const;
  Writer& writer();
  const Writer& writer() const;

  void set_error() { error_ = true; };       // Signal that the stream suffered an error.
  bool has_error() const { return error_; }; // Has the stream had an error?

protected:
  // Please add any additional state to the ByteStream here, and not to the Writer and Reader interfaces.
  uint64_t capacity_;//this whole capacity in the ByteStream
  std::string buffer{};//the ByteStream buffer(pipe)
  bool error_ {};
  bool is_EOF_{};//to check whether is the end of byte_stream or not 
  uint64_t push_cnt{};//push_cnt record
  uint64_t pop_cnt{};//pop_cnt record
};
 ```
 ### In the lab0,ByteStream model is similar to the producer-consumer model
 - One Reader 
 - One Writer
 - One buffer pipe to transmiss the ByteStream

![basic_model](/cs144%20Note/image/lab0/basic_model.png)
### What is available_capacity and buffer.size()?
![basic_model](/cs144%20Note/image/lab0/model_detail.png)
- The value of the buffer.size() tell you how much byte size in your buffer at present.
- available_capacity() is a function to tell you how much capacity we can use for the next time. 

# Target: Complete 5 Function in Writer and Reader
## Writer Part :
```
bool Writer::is_closed() const
{
  // Your code here.
  //return is_EOF value
}

void Writer::push( string data )
{
  // Your code here.
  // conditional part,you should to check
  
  //compare the data.length with the available_capacity() ,then choose the min one.
  //append the data substring into the buffer
  //increase the push_cnt. 
}

void Writer::close()
{
  // Your code here.
  //change the is_EOF value(false) to true;
}

uint64_t Writer::available_capacity() const
{
  // Your code here.
  return capacity_ - buffer.size();
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  //return push_cnt;
}
```

## Reader Part :
```
bool Reader::is_finished() const
{
  // Your code here.
  //return,only when is_EOF is true and push_cnt equals to pop_cnt as well. 
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  //return pop_cnt;
}

string_view Reader::peek() const
{
  // Your code here.
  // conditional part,you should to check

  //return a string_view type value
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  // conditional part,you should to check

  //compare the len with the buffer.size(),then choose the min one.
  //change the buffer value
  //increase the pop_cnt.  
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  //return buffer.size;
}
```

# My Grade:
![my_grade](/cs144%20Note/image/lab0/my_grade.png)



