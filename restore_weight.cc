#include "tensorflow/core/framework/op_kernel.h"
#include "tensorflow/core/framework/tensor_shape.h"
#include "tensorflow/core/platform/default/logging.h"
#include "tensorflow/core/framework/shape_inference.h"

using namespace tensorflow;

/*
    Register Dense operation
*/

REGISTER_OP("Dense")
  .Input("index: DT_STRING")
  .Input("centers: DT_FLOAT")
  .Input("shape: DT_INT32")
  .Input("huffman_len: DT_INT32")
  .Output("output: DT_FLOAT")
  .Doc(R"doc(
  Use index and centers to restore the weights in original structure,
  and pass to the conv2d op. Cannot only index and centers because of the
  specific way Eigen choose to do the convolution.
  )doc");

/*
    Dense Operation CPU
*/

class RestoreWeightOpCPU : public OpKernel {
public:
  explicit RestoreWeightOpCPU(OpKernelConstruction* context) : OpKernel(context) {
  }
  
  void Compute(OpKernelContext* context) override {
    //printf("RestoreWeightOpCPU\n");

    // get the index tensor(the last byte is the length info)
    const Tensor& index = context->input(0);
    
    // get the centers tensor
    const Tensor& centers = context->input(1);
      
    // get the shape tensor
    const Tensor& shape = context->input(2);
    
    //Check that centers are two dimensional
    DCHECK_EQ(centers.dims(), 2);
    
    int output_depth = shape(0);
    int input_depth = shape(1);
    int filter_width = shape(2);
    int filter_height = shape(3);

    // create output shape
    TensorShape output_shape;
    //printf("batch_samples: %d\n", batch_samples);
    //printf("units: %d\n", units);

    output_shape.AddDim(output_depth);
    output_shape.AddDim(filter_height);
    output_shape.AddDim(filter_width);
    output_shape.AddDim(input_depth);
            
    // create output tensor
    Tensor* output = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(0, output_shape, &output));
    
    // get the corresponding Eigen tensors for data access
    auto centers_tensor = centers.flat<DT_FLOAT>();
    
    


    


  }
};

REGISTER_KERNEL_BUILDER(Name("RestoreWeight").Device(DEVICE_CPU), RestoreWeightOpCPU);

