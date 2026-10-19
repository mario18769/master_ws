#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to robot_interfaces__msg__ObjectPose

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ObjectPose {

    // This member is not documented.
    #[allow(missing_docs)]
    pub object_type: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub axis_x: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub axis_y: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub axis_z: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub axis_pt_x: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub axis_pt_y: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub axis_pt_z: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub q_x: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub q_y: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub q_z: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub q_w: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub radius: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub length: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mid_x: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mid_y: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mid_z: f64,

}



impl Default for ObjectPose {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::ObjectPose::default())
  }
}

impl rosidl_runtime_rs::Message for ObjectPose {
  type RmwMsg = super::msg::rmw::ObjectPose;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        object_type: msg.object_type.as_str().into(),
        axis_x: msg.axis_x,
        axis_y: msg.axis_y,
        axis_z: msg.axis_z,
        axis_pt_x: msg.axis_pt_x,
        axis_pt_y: msg.axis_pt_y,
        axis_pt_z: msg.axis_pt_z,
        q_x: msg.q_x,
        q_y: msg.q_y,
        q_z: msg.q_z,
        q_w: msg.q_w,
        radius: msg.radius,
        length: msg.length,
        mid_x: msg.mid_x,
        mid_y: msg.mid_y,
        mid_z: msg.mid_z,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        object_type: msg.object_type.as_str().into(),
      axis_x: msg.axis_x,
      axis_y: msg.axis_y,
      axis_z: msg.axis_z,
      axis_pt_x: msg.axis_pt_x,
      axis_pt_y: msg.axis_pt_y,
      axis_pt_z: msg.axis_pt_z,
      q_x: msg.q_x,
      q_y: msg.q_y,
      q_z: msg.q_z,
      q_w: msg.q_w,
      radius: msg.radius,
      length: msg.length,
      mid_x: msg.mid_x,
      mid_y: msg.mid_y,
      mid_z: msg.mid_z,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      object_type: msg.object_type.to_string(),
      axis_x: msg.axis_x,
      axis_y: msg.axis_y,
      axis_z: msg.axis_z,
      axis_pt_x: msg.axis_pt_x,
      axis_pt_y: msg.axis_pt_y,
      axis_pt_z: msg.axis_pt_z,
      q_x: msg.q_x,
      q_y: msg.q_y,
      q_z: msg.q_z,
      q_w: msg.q_w,
      radius: msg.radius,
      length: msg.length,
      mid_x: msg.mid_x,
      mid_y: msg.mid_y,
      mid_z: msg.mid_z,
    }
  }
}


