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
fn read_binary_file(file_name: &str) -> Result<Vec<u8>, String>{
    let raw_data = fs::read(file_name);
    let data = match raw_data {
        Ok(data) => data,
        Err(e) => return Err(format!("Error reading file: {}", e)),
    };
    Ok(data)
}

#[allow(dead_code)]
fn write_binary_to_file(file_path: &str, data: Vec<u8>) -> std::io::Result<()> {
    fs::write(file_path, data)?;
    Ok(())
}

#[allow(dead_code)]
fn group_u8_to_f64(bytes: &[u8]) -> Vec<f64> {
    bytes
        .chunks_exact(8)  // Take chunks of 8 bytes
        .map(|chunk| {
            let mut value_bytes = [0; 8];
            value_bytes.copy_from_slice(chunk);
            f64::from_bits(u64::from_le_bytes(value_bytes))
        })
        .collect()
}

#[allow(dead_code)]
fn split_f64_to_u8(values: &[f64]) -> Vec<u8> {
    values
        .iter()
        .flat_map(|&f| {
            let bits = f.to_bits();
            (0..8).map(move |shift| ((bits >> (shift * 8)) & 0xFF) as u8)
        })
        .collect()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn writes_binary_file() {
        let double_data: Vec<f64> = vec![10.352012, -5.0272, 3.0, -2.0899];
        let bytes = split_f64_to_u8(&double_data);
        let file_path: &str = "./testTrace.bin";
        let raw_data = write_binary_to_file(file_path, bytes);
        println!("Gather: {:?}", raw_data)
    }


    #[test]
    fn reads_binary_file() {
        let file_path: &str = "./resources/shot6220.bin";
        let raw_data = read_binary_file(file_path);
        println!("Gather: {:?}", raw_data)
    }
}
