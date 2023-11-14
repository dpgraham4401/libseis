use std::fs;
use std::io::Read;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Precision {
    Single,
    Double,
}

#[derive(Debug)]
pub struct Gather<T> {
    pub id: u16,
    pub nt: u16,
    pub nx: u16,
    pub dt: f32,
    pub data: Option<Box<T>>,
    precision: Option<Precision>,
}

#[allow(dead_code)]
pub fn read_binary_file(file_name: &str) -> Result<Vec<u8>, String>{
    let raw_data = fs::read(file_name);
    let data = match raw_data {
        Ok(data) => data,
        Err(e) => return Err(format!("Error reading file: {}", e)),
    };
    Ok(data)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn reads_binary_file() {
        let file_path: &str = "./resources/shot6220.bin";
        let raw_data = read_binary_file(file_path);
        println!("Gather: {:?}", raw_data)
    }
}
