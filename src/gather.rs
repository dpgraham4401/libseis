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
    pub data: Option<Vec<T>>,
    precision: Option<Precision>,
}

fn read_binary_file(file_name: &str) -> Vec<u8> {
    let mut file = std::fs::File::open(file_name).unwrap();
    let mut buffer = Vec::new();
    file.read_to_end(&mut buffer).unwrap();
    buffer
}

fn load_data_into_gather<T>(path: &str, time_sampling: f32, samples_per_trace: u16, number_of_traces: u16 ) -> Gather<T> {
    let data_from_file = read_binary_file(path);
    Gather {
        id: 1,
        dt: time_sampling,
        nt: samples_per_trace,
        nx: number_of_traces,
        precision: None,
        data: None,
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        assert_eq!(2, 2);
    }

    #[test]
    fn reads_binary_file() {
        let file_path: &str = "./resources/shot6220.bin";
        let gather = load_data_into_gather(file_path, 0.004, 3101, 1000);
        println!("Gather: {:?}", gather)
    }
}
