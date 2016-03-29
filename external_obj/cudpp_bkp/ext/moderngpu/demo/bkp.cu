////////////////////////////////////////////////////////////////////////////////
// LocalitySortKeys

void DemoLocalitySortKeys(CudaContext& context) {

	// Generate keys that are roughly sorted but with added noise.
	int N = 100;
	std::vector<int> keysHost(N);
	for(int i = 0; i < N; ++i) 
		keysHost[i] = i + Rand(0, 25);

	MGPU_MEM(int) keys = context.Malloc(keysHost);


	// Sort by exploiting locality.
	LocalitySortKeys(keys->get(), N, context);

}

////////////////////////////////////////////////////////////////////////////////
// LocalitySortPairs

void DemoLocalitySortPairs(CudaContext& context) {

	// Generate keys that are roughly sorted but with added noise.
	int N = 100;
	std::vector<int> keysHost(N);
	for(int i = 0; i < N; ++i) 
		keysHost[i] = i + Rand(0, 25);

	MGPU_MEM(int) keys = context.Malloc(keysHost);
	MGPU_MEM(int) values = context.FillAscending<int>(N, 0, 1);


	// Sort by exploiting locality.
	LocalitySortPairs(keys->get(), values->get(), N, context);

	
}

////////////////////////////////////////////////////////////////////////////////
// SortedSearch

void DemoSortedSearch(CudaContext& context) {

	// Use CudaContext::SortRandom to generate a haystack of 200 random integers
	// between 0 and 999 and an array of 100 needles in the same range.
	int HaystackSize = 200;
	int NeedlesSize = 100;
	MGPU_MEM(int) haystack = context.SortRandom<int>(HaystackSize, 0, 299);
	MGPU_MEM(int) needles = context.SortRandom<int>(NeedlesSize, 0, 299);


	// Run a vectorized sorted search to find lower bounds.
	SortedSearch<MgpuBoundsLower>(needles->get(), NeedlesSize, haystack->get(),
		HaystackSize, needles->get(), context);

}

void DemoSortedSearch2(CudaContext& context) {

	int ACount = 100;
	int BCount = 100;
	MGPU_MEM(int) aData = context.SortRandom<int>(ACount, 0, 299);
	MGPU_MEM(int) bData = context.SortRandom<int>(BCount, 0, 299);
	MGPU_MEM(int) aIndices = context.Malloc<int>(ACount);
	MGPU_MEM(int) bIndices = context.Malloc<int>(BCount);


	// Run a vectorized sorted search to find lower bounds.
	SortedSearch<MgpuBoundsLower, MgpuSearchTypeIndexMatch,
		MgpuSearchTypeIndexMatch>(aData->get(), ACount, bData->get(), BCount,
		aIndices->get(), bIndices->get(), context);

}

////////////////////////////////////////////////////////////////////////////////
// LoadBalancingSearch

void DemoLBS(CudaContext& context) {
	
	// Use CudaContext::GenRandom to generate work counts between 0 and 5.
	int N = 50;
	MGPU_MEM(int) counts = context.GenRandom<int>(N, 0, 5);
	

	// Scan the counts.
	int total;
	ScanExc(counts->get(), N, &total, context);

	// Allocate space for the object references and run load-balancing search.
	MGPU_MEM(int) refsData = context.Malloc<int>(total);
	LoadBalanceSearch(total, counts->get(), N, refsData->get(), context);

}

////////////////////////////////////////////////////////////////////////////////
// IntervalExpand

void DemoIntervalExpand(CudaContext& context) {

	const int NumInputs = 20;
	const int Counts[NumInputs] = { 
		2, 5, 7, 16, 0, 1, 0, 0, 14, 10, 
		3, 14, 2, 1, 11, 2, 1, 0, 5, 6 
	};
	const int Inputs[NumInputs] = {
		1, 1, 2, 3, 5, 8, 13, 21, 34, 55,
		89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765
	};


	MGPU_MEM(int) countsDevice = context.Malloc(Counts, NumInputs);
	int total;
	ScanExc(countsDevice->get(), NumInputs, &total, context);

	MGPU_MEM(int) fillDevice = context.Malloc(Inputs, NumInputs);

	MGPU_MEM(int) dataDevice = context.Malloc<int>(total);
	IntervalExpand(total, countsDevice->get(), fillDevice->get(), NumInputs, 
		dataDevice->get(), context);
	
}

////////////////////////////////////////////////////////////////////////////////
// IntervalMove

void DemoIntervalMove(CudaContext& context) {

	const int NumInputs = 20;
	const int Counts[NumInputs] = {
		3, 9, 1, 9, 8, 5, 10, 2, 5, 2,
		8, 6, 5, 2, 4, 0, 8, 2, 5, 6
	};
	const int Gather[NumInputs] = {
		75, 86, 17, 2, 67, 24, 37, 11, 95, 35,
		52, 18, 47, 0, 13, 75, 78, 60, 62, 29
	};
	const int Scatter[NumInputs] = {
		10, 80, 99, 27, 41, 71, 15, 0, 36, 13,
		89, 49, 66, 97, 76, 76, 2, 25, 61, 55
	};




	MGPU_MEM(int) countsDevice = context.Malloc(Counts, NumInputs);
	MGPU_MEM(int) gatherDevice = context.Malloc(Gather, NumInputs);
	MGPU_MEM(int) scatterDevice = context.Malloc(Scatter, NumInputs);
	int total;
	ScanExc(countsDevice->get(), NumInputs, &total, context);

	MGPU_MEM(int) dataDevice = context.Malloc<int>(total);

	IntervalMove(total, gatherDevice->get(), scatterDevice->get(), 
		countsDevice->get(), NumInputs, mgpu::counting_iterator<int>(0),
		dataDevice->get(), context);

} 

////////////////////////////////////////////////////////////////////////////////
// Join

void DemoJoin(CudaContext& context) {

	int ACount = 30;
	int BCount = 30;

	MGPU_MEM(int) aKeysDevice = context.SortRandom<int>(ACount, 100, 130);
	MGPU_MEM(int) bKeysDevice = context.SortRandom<int>(BCount, 100, 130);
	std::vector<int> aKeysHost, bKeysHost;
	aKeysDevice->ToHost(aKeysHost);
	bKeysDevice->ToHost(bKeysHost);



	MGPU_MEM(int) aIndices, bIndices;
	int innerCount = RelationalJoin<MgpuJoinKindInner>(aKeysDevice->get(),
		ACount, bKeysDevice->get(), BCount, &aIndices, &bIndices, context);

	std::vector<int> aHost, bHost;
	aIndices->ToHost(aHost);
	bIndices->ToHost(bHost);

	for(int i = 0; i < innerCount; ++i)
			aKeysHost[aHost[i]], bKeysHost[bHost[i]]);

	int outerCount = RelationalJoin<MgpuJoinKindOuter>(aKeysDevice->get(),
		ACount, bKeysDevice->get(), BCount, &aIndices, &bIndices, context);

	aIndices->ToHost(aHost);
	bIndices->ToHost(bHost);
	for(int i = 0; i < outerCount; ++i) {
		std::string aKey, bKey;
			(-1 != aHost[i]) ? aKey.c_str() : "---", 
			(-1 != bHost[i]) ? bKey.c_str() : "---");
	}
}

////////////////////////////////////////////////////////////////////////////////
// SetsKeys

void DemoSetsKeys(CudaContext& context) {

	// Use CudaContext::SortRandom to generate 100 random sorted integers 
	// between 0 and 99.
	int N = 100;
	MGPU_MEM(int) aData = context.SortRandom<int>(N, 0, 99);
	MGPU_MEM(int) bData = context.SortRandom<int>(N, 0, 99);

	
	MGPU_MEM(int) intersectionDevice;
	SetOpKeys<MgpuSetOpIntersection, true>(aData->get(), N, bData->get(), N,
		&intersectionDevice, context, false);


	MGPU_MEM(int) symDiffDevice;
	SetOpKeys<MgpuSetOpSymDiff, true>(aData->get(), N, bData->get(), N,
		&symDiffDevice, context, false);

}

////////////////////////////////////////////////////////////////////////////////
// SetsPairs

void DemoSetsPairs(CudaContext& context) {

	// Use CudaContext::SortRandom to generate 100 random sorted integers 
	// between 0 and 99.
	int N = 100;
	MGPU_MEM(int) aData = context.SortRandom<int>(N, 0, 99);
	MGPU_MEM(int) bData = context.SortRandom<int>(N, 0, 99);

	
	MGPU_MEM(int) intersectionDevice, intersectionValues;
	SetOpPairs<MgpuSetOpIntersection, true>(aData->get(), 
		mgpu::counting_iterator<int>(0), N, bData->get(), 
		mgpu::counting_iterator<int>(N), N, &intersectionDevice,
		&intersectionValues, context);



	MGPU_MEM(int) symDiffDevice, symDiffValues;
	SetOpPairs<MgpuSetOpSymDiff, true>(aData->get(), 
		mgpu::counting_iterator<int>(0), N, bData->get(), 
		mgpu::counting_iterator<int>(N), N, &symDiffDevice, &symDiffValues, 
		context);


}

////////////////////////////////////////////////////////////////////////////////
// ReduceByKey

void DemoReduceByKey(CudaContext& context) {

	int count = 100;
	std::vector<int> keys(count);
	for(int i = 1; i < count; ++i)
		keys[i] = keys[i - 1] + (0 == Rand(0, 9));

	MGPU_MEM(int) keysDevice = context.Malloc(keys);
	MGPU_MEM(int) valsDevice = context.GenRandom<int>(count, 1, 5);



	MGPU_MEM(int) keysDestDevice = context.Malloc<int>(count);
	MGPU_MEM(int) destDevice = context.Malloc<int>(count);

	int numSegments;
	ReduceByKey(keysDevice->get(), valsDevice->get(), count,
		0, mgpu::plus<int>(), mgpu::equal_to<int>(), destDevice->get(),
		keysDestDevice->get(), &numSegments, (int*)0, context);


}

////////////////////////////////////////////////////////////////////////////////
// DemoSegReduceCsr

void DemoSegReduceCsr(CudaContext& context) {

	int count = 100;
	const int SegmentStarts[] = {
		0, 9, 19, 25, 71, 87, 97
	};
	const int NumSegments = sizeof(SegmentStarts) / sizeof(int);
	MGPU_MEM(int) csrDevice = context.Malloc(SegmentStarts, NumSegments);
	MGPU_MEM(int) valsDevice = context.GenRandom<int>(count, 1, 5);

	MGPU_MEM(int) resultsDevice = context.Malloc<int>(NumSegments);
	SegReduceCsr(valsDevice->get(), csrDevice->get(), count, NumSegments,
		false, resultsDevice->get(), (int)0, mgpu::plus<int>(), context);

}

