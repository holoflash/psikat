use crate::project::Project;
use crate::project::file;

pub struct Demo {
    pub name: &'static str,
    pub data: &'static [u8],
}

pub const DEMOS: &[Demo] = &[Demo {
    name: "The Entertainer",
    data: include_bytes!("./the_entertainer.psikat"),
}];

pub fn load_demo(demo: &Demo) -> Result<Project, String> {
    file::load_bytes(demo.data)
}
