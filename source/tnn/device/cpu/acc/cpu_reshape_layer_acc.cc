// Tencent is pleased to support the open source community by making TNN available.
//
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include "tnn/device/cpu/acc/cpu_layer_acc.h"
#include "tnn/utils/data_type_utils.h"

namespace TNN_NS {

DECLARE_CPU_ACC(Reshape, LAYER_RESHAPE);

Status CpuReshapeLayerAcc::Reshape(const std::vector<Blob *> &inputs, const std::vector<Blob *> &outputs) {
    return TNN_OK;
}

Status CpuReshapeLayerAcc::Forward(const std::vector<Blob *> &inputs, const std::vector<Blob *> &outputs) {
    auto input  = inputs[0];
    auto output = outputs[0];

    if (output->GetHandle().base != input->GetHandle().base) {
        auto dims_input    = input->GetBlobDesc().dims;
        int data_byte_size = DataTypeUtils::GetBytesSize(output->GetBlobDesc().data_type);
        auto size_in_bytes = dims_input[0] * dims_input[1] * dims_input[2] * dims_input[3] * data_byte_size;
        memcpy(output->GetHandle().base, input->GetHandle().base, size_in_bytes);
    }
    return TNN_OK;
}

REGISTER_CPU_ACC(Reshape, LAYER_RESHAPE);

}  // namespace TNN_NS
