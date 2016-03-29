typedef CUDPPHashTableInternal<CudaHT::CuckooHashing::HashTable> hti_basic;
typedef CUDPPHashTableInternal<CudaHT::CuckooHashing::CompactingHashTable> hti_compacting;
typedef CUDPPHashTableInternal<CudaHT::CuckooHashing::MultivalueHashTable> hti_multivalue;
typedef CUDPPHashTableInternal<void> hti_void;

CUDPP_DLL
CUDPPResult
cudppHashTable(CUDPPHandle cudppHandle, CUDPPHandle *plan,
               const CUDPPHashTableConfig *config)
{
    // first check: is this device >= 2.0? if not, return error
    CUDPPManager *mgr = CUDPPManager::getManagerFromHandle(cudppHandle);
    cudaDeviceProp prop;
    mgr->getDeviceProps(prop);
    
    if (prop.major < 2)
    {
        return CUDPP_ERROR_ILLEGAL_CONFIGURATION;
    }

    switch(config->type)
    {
    case CUDPP_BASIC_HASH_TABLE:
    {
        CudaHT::CuckooHashing::HashTable * basic_table = 
            new CudaHT::CuckooHashing::HashTable();
        basic_table->setTheCudpp(cudppHandle);
        basic_table->Initialize(config->kInputSize, config->space_usage);
        hti_basic * hti = new hti_basic(config, basic_table);
        if (!hti)
        {
            return CUDPP_ERROR_UNKNOWN;
        }
        else
        {
            *plan = hti->getHandle();
            return CUDPP_SUCCESS;
        }
        break;
    }
    case CUDPP_COMPACTING_HASH_TABLE:
    {
        CudaHT::CuckooHashing::CompactingHashTable * compacting_table = 
            new CudaHT::CuckooHashing::CompactingHashTable();
        compacting_table->setTheCudpp(cudppHandle);
        compacting_table->Initialize(config->kInputSize, config->space_usage);
        hti_compacting * hti = new hti_compacting(config, compacting_table);
        if (!hti)
        {
            return CUDPP_ERROR_UNKNOWN;
        }
        else
        {
            *plan = hti->getHandle();
            return CUDPP_SUCCESS;
        }
        break;
    }
    case CUDPP_MULTIVALUE_HASH_TABLE:
    {
        CudaHT::CuckooHashing::MultivalueHashTable * multivalue_table = 
            new CudaHT::CuckooHashing::MultivalueHashTable();
        multivalue_table->setTheCudpp(cudppHandle);
        multivalue_table->Initialize(config->kInputSize, config->space_usage);
        hti_multivalue * hti = new hti_multivalue(config, multivalue_table);
        if (!hti)
        {
            return CUDPP_ERROR_UNKNOWN;
        }
        else
        {
            *plan = hti->getHandle();
            return CUDPP_SUCCESS;
        }
        break;
    }
    case CUDPP_INVALID_HASH_TABLE:
        return CUDPP_ERROR_ILLEGAL_CONFIGURATION;
        break;
    }
    return CUDPP_ERROR_ILLEGAL_CONFIGURATION;
}

CUDPP_DLL CUDPPResult cudppHashInsert(CUDPPHandle plan, const void* d_keys, const void* d_vals, size_t num)
{
    // the other way to do this hacky thing is to have inherited classes
    // from CUDPPHashTableInternal maybe?
    hti_void * hti_init = (hti_void *) getPlanPtrFromHandle<hti_void>(plan);
    switch(hti_init->config.type)
    {
    case CUDPP_BASIC_HASH_TABLE:
    {
        hti_basic * hti = (hti_basic *) getPlanPtrFromHandle<hti_basic>(plan);
        bool s = hti->hash_table->Build(num, (const unsigned int *) d_keys, 
                                        (const unsigned int *) d_vals);
        return s ? CUDPP_SUCCESS : CUDPP_ERROR_UNKNOWN;
        break;
    }
    case CUDPP_COMPACTING_HASH_TABLE:
    {
        hti_compacting * hti =
            (hti_compacting *) getPlanPtrFromHandle<hti_compacting>(plan);
        bool s = hti->hash_table->Build(num, (const unsigned int *) d_keys, 
                                        (const unsigned int *) d_vals);
        return s ? CUDPP_SUCCESS : CUDPP_ERROR_UNKNOWN;
        break;
    } 
    case CUDPP_MULTIVALUE_HASH_TABLE:
    {
        hti_multivalue * hti =
            (hti_multivalue *) getPlanPtrFromHandle<hti_multivalue>(plan);
        bool s = hti->hash_table->Build(num, (const unsigned int *) d_keys, 
                                        (const unsigned int *) d_vals);
        return s ? CUDPP_SUCCESS : CUDPP_ERROR_UNKNOWN;
        break;
    } 
    case CUDPP_INVALID_HASH_TABLE:
        return CUDPP_ERROR_ILLEGAL_CONFIGURATION;
        break;
    }
    return CUDPP_ERROR_ILLEGAL_CONFIGURATION;
}

CUDPP_DLL CUDPPResult cudppHashRetrieve(CUDPPHandle plan, const void* d_keys, void* d_vals, size_t num)
{
    hti_void * hti_init = (hti_void *) getPlanPtrFromHandle<hti_void>(plan);
    switch(hti_init->config.type)
    {
    case CUDPP_BASIC_HASH_TABLE:
    {
        hti_basic * hti = (hti_basic *) getPlanPtrFromHandle<hti_basic>(plan);
        hti->hash_table->Retrieve(num, (const unsigned int *) d_keys, 
                                           (unsigned int *) d_vals);
        return CUDPP_SUCCESS;
        break;
    }
    case CUDPP_COMPACTING_HASH_TABLE:
    {
        hti_compacting * hti = 
            (hti_compacting *) getPlanPtrFromHandle<hti_compacting>(plan);
        hti->hash_table->Retrieve(num, (const unsigned int *) d_keys, 
                                  (unsigned int *) d_vals);
        return CUDPP_SUCCESS;
        break;
    }
    case CUDPP_MULTIVALUE_HASH_TABLE:
    {
        hti_multivalue * hti = 
            (hti_multivalue *) getPlanPtrFromHandle<hti_multivalue>(plan);
        hti->hash_table->Retrieve(num, (const unsigned int *) d_keys, 
                                  (uint2 *) d_vals);
        return CUDPP_SUCCESS;
        break;
    }
    case CUDPP_INVALID_HASH_TABLE:
        return CUDPP_ERROR_ILLEGAL_CONFIGURATION;
        break;
    }
    return CUDPP_ERROR_ILLEGAL_CONFIGURATION;
}

CUDPP_DLL CUDPPResult cudppDestroyHashTable(CUDPPHandle cudppHandle, CUDPPHandle plan)
{
    (void) cudppHandle;         // eliminates doxygen (!) warning
    hti_void * hti_init = (hti_void *) getPlanPtrFromHandle<hti_void>(plan);
    switch(hti_init->config.type)
    {
    case CUDPP_BASIC_HASH_TABLE:
    {
        hti_basic * hti = (hti_basic *) getPlanPtrFromHandle<hti_basic>(plan);
        delete hti;
        return CUDPP_SUCCESS;
    }
    case CUDPP_COMPACTING_HASH_TABLE:
    {
        hti_compacting * hti = 
            (hti_compacting *) getPlanPtrFromHandle<hti_compacting>(plan);
        delete hti;
        return CUDPP_SUCCESS;
    }
    case CUDPP_MULTIVALUE_HASH_TABLE:
    {
        hti_multivalue * hti = 
            (hti_multivalue *) getPlanPtrFromHandle<hti_multivalue>(plan);
        delete hti;
        return CUDPP_SUCCESS;
    }
    case CUDPP_INVALID_HASH_TABLE:
        return CUDPP_ERROR_ILLEGAL_CONFIGURATION;
        break;
    }
    return CUDPP_ERROR_ILLEGAL_CONFIGURATION;
}

CUDPP_DLL CUDPPResult cudppMultivalueHashGetValuesSize(CUDPPHandle plan, unsigned int * size)
{
    hti_void * hti_init = (hti_void *) getPlanPtrFromHandle<hti_void>(plan);
    if (hti_init->config.type != CUDPP_MULTIVALUE_HASH_TABLE)
    {
        // better be a MULTIVALUE
        return CUDPP_ERROR_ILLEGAL_CONFIGURATION;
    }
    hti_multivalue * hti = 
        (hti_multivalue *) getPlanPtrFromHandle<hti_multivalue>(plan);
    *size = hti->hash_table->get_values_size();
    return CUDPP_SUCCESS;
}

CUDPPResult cudppMultivalueHashGetAllValues(CUDPPHandle plan, unsigned int ** d_vals)
{
    hti_void * hti_init = (hti_void *) getPlanPtrFromHandle<hti_void>(plan);
    if (hti_init->config.type != CUDPP_MULTIVALUE_HASH_TABLE)
    {
        // better be a MULTIVALUE
        return CUDPP_ERROR_ILLEGAL_CONFIGURATION;
    }
    hti_multivalue * hti = 
        (hti_multivalue *) getPlanPtrFromHandle<hti_multivalue>(plan);
    // @TODO fix up constness
    *d_vals = (unsigned*) (hti->hash_table->get_all_values());
    return CUDPP_SUCCESS;
}
