
#[derive()]
pub struct Gather {
    id: u16,
    number_time_samples: u16,
    number_traces: u16,
    time_sampling: f32,
    data: Vec<f32>,
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        assert_eq!(2, 2);
    }
}
