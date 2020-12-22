// Auto-generated. Do not edit!

// (in-package uwb_localization_description.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class position_data_uwb {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.destination_id = null;
      this.distance = null;
      this.stamp = null;
      this.uwb_position = null;
    }
    else {
      if (initObj.hasOwnProperty('destination_id')) {
        this.destination_id = initObj.destination_id
      }
      else {
        this.destination_id = [];
      }
      if (initObj.hasOwnProperty('distance')) {
        this.distance = initObj.distance
      }
      else {
        this.distance = [];
      }
      if (initObj.hasOwnProperty('stamp')) {
        this.stamp = initObj.stamp
      }
      else {
        this.stamp = [];
      }
      if (initObj.hasOwnProperty('uwb_position')) {
        this.uwb_position = initObj.uwb_position
      }
      else {
        this.uwb_position = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type position_data_uwb
    // Serialize message field [destination_id]
    bufferOffset = _arraySerializer.int64(obj.destination_id, buffer, bufferOffset, null);
    // Serialize message field [distance]
    bufferOffset = _arraySerializer.float64(obj.distance, buffer, bufferOffset, null);
    // Serialize message field [stamp]
    bufferOffset = _arraySerializer.time(obj.stamp, buffer, bufferOffset, null);
    // Serialize message field [uwb_position]
    bufferOffset = _arraySerializer.float64(obj.uwb_position, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type position_data_uwb
    let len;
    let data = new position_data_uwb(null);
    // Deserialize message field [destination_id]
    data.destination_id = _arrayDeserializer.int64(buffer, bufferOffset, null)
    // Deserialize message field [distance]
    data.distance = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [stamp]
    data.stamp = _arrayDeserializer.time(buffer, bufferOffset, null)
    // Deserialize message field [uwb_position]
    data.uwb_position = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.destination_id.length;
    length += 8 * object.distance.length;
    length += 8 * object.stamp.length;
    length += 8 * object.uwb_position.length;
    return length + 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'uwb_localization_description/position_data_uwb';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'cffdb089f0ead7804716b039674b3438';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int64[] destination_id
    float64[] distance
    time[] stamp
    float64[] uwb_position
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new position_data_uwb(null);
    if (msg.destination_id !== undefined) {
      resolved.destination_id = msg.destination_id;
    }
    else {
      resolved.destination_id = []
    }

    if (msg.distance !== undefined) {
      resolved.distance = msg.distance;
    }
    else {
      resolved.distance = []
    }

    if (msg.stamp !== undefined) {
      resolved.stamp = msg.stamp;
    }
    else {
      resolved.stamp = []
    }

    if (msg.uwb_position !== undefined) {
      resolved.uwb_position = msg.uwb_position;
    }
    else {
      resolved.uwb_position = []
    }

    return resolved;
    }
};

module.exports = position_data_uwb;
